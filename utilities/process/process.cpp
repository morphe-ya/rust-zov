#include "process.hpp"

#include "../definitions/definitions.hpp"
#include "../memory/memory.hpp"
#include "../value/value.hpp"
#include "../hash/hash.hpp"

#define contains_record( address, type, field ) ( ( type* )( ( char* )( address ) - ( uint64_t )( &( ( type* )0 )->field ) ) )

namespace process {
    uint64_t get_module_base( uint64_t hash ) {
        const auto& peb = reinterpret_cast< ppeb_t >( __readgsqword( o( 0x60 ) ) );
        const auto& head = peb->m_ldr->m_in_memory_order_module_list;

        for ( auto current{ head }; current.Flink != &peb->m_ldr->m_in_memory_order_module_list; current = *current.Flink ) {
            const auto& entry = reinterpret_cast< pldr_data_table_entry_t >( contains_record( current.Flink, ldr_data_table_entry_t, m_in_memory_order_links ) );

            if ( !entry->m_base_dll_name.Buffer )
                continue;

            char name[ 256 ]{ };

            for ( int i{ }; i != ( entry->m_base_dll_name.Length / 2 ) - 4; ++i )
                name[ i ] = to_lower( entry->m_base_dll_name.Buffer[ i ] );

            if ( HASH_RT( name ) == hash )
                return entry->m_dll_base;
        }

        return 0;
    }

    uint64_t find_import( uint64_t base, uint64_t hash ) {
        const auto& nt_headers = reinterpret_cast< IMAGE_NT_HEADERS64* >( base + reinterpret_cast< IMAGE_DOS_HEADER* >( base )->e_lfanew );

        if ( nt_headers->Signature != o( 0x4550 ) )
            return 0;

        const auto& data_directory = reinterpret_cast< IMAGE_DATA_DIRECTORY* >( &nt_headers->OptionalHeader.DataDirectory[ 1 ] );

        if ( !data_directory->Size
             || !data_directory->VirtualAddress )
            return 0;

        const auto& import_descriptor = reinterpret_cast< IMAGE_IMPORT_DESCRIPTOR* >( base + data_directory->VirtualAddress );

        if ( !import_descriptor->OriginalFirstThunk
             || !import_descriptor->FirstThunk )
            return false;

        auto descriptor{ import_descriptor };

        do {
            const auto& name = reinterpret_cast< const char* >( base + descriptor->Name );

            if ( !name )
                continue;

            auto thunk_data = reinterpret_cast< IMAGE_THUNK_DATA* >( base + descriptor->OriginalFirstThunk );
            int count{ };

            while ( thunk_data && thunk_data->u1.AddressOfData ) {
                const auto& import = reinterpret_cast< IMAGE_IMPORT_BY_NAME* >( base + thunk_data->u1.AddressOfData );

                if ( !import )
                    continue;

                if ( HASH_RT( import->Name ) == hash )
                    return base + descriptor->FirstThunk + ( count * sizeof( uint64_t ) );

                ++thunk_data;
                ++count;
            }

            ++descriptor;
        } while ( ( descriptor ) && descriptor->Name );

        return 0;
    }

    uint64_t find_export( uint64_t base, uint64_t hash ) {
        const auto& nt_headers = reinterpret_cast< IMAGE_NT_HEADERS64* >( base + reinterpret_cast< IMAGE_DOS_HEADER* >( base )->e_lfanew );

        if ( nt_headers->Signature != o( 0x4550 ) )
            return 0;

        const auto& data_directory = reinterpret_cast< IMAGE_DATA_DIRECTORY* >( &nt_headers->OptionalHeader.DataDirectory[ 0 ] );

        if ( !data_directory->Size 
             || !data_directory->VirtualAddress )
            return 0;

        const auto& export_directory = reinterpret_cast< IMAGE_EXPORT_DIRECTORY* >( base + data_directory->VirtualAddress );

        if ( !export_directory->AddressOfFunctions 
             || !export_directory->AddressOfNames 
             || !export_directory->AddressOfNameOrdinals )
            return false;

        const auto& rva_table = reinterpret_cast< uint32_t* >( base + export_directory->AddressOfFunctions );
        const auto& name_table = reinterpret_cast< uint32_t* >( base + export_directory->AddressOfNames );
        const auto& ordinal_table = reinterpret_cast< uint16_t* >( base + export_directory->AddressOfNameOrdinals );

        for ( int i{ }; i < export_directory->NumberOfNames; ++i ) {
            const auto& name = reinterpret_cast< const char* >( base + name_table[ i ] );

            if ( HASH_RT( name ) == hash )
                return base + rva_table[ ordinal_table[ i ] ];
        }

        return 0;
    }

    HANDLE get_current_process_token( ) {
        return reinterpret_cast< HANDLE >( o( -4 ) );
    }

    uint32_t get_current_process_id( ) {
        return memory::read< uint32_t >( __readgsqword( o( 0x30 ) ) + o( 0x40 ) );
    }

    uint32_t get_current_thread_id( ) {
        return memory::read< uint32_t >( __readgsqword( o( 0x30 ) ) + o( 0x48 ) );
    }

    HANDLE get_current_process( ) {
        return reinterpret_cast< HANDLE >( o( -1 ) );
    }

    HANDLE get_current_thread( ) {
        return reinterpret_cast< HANDLE >( o( -2 ) );
    }

    HANDLE get_process_heap( ) {
        return memory::read< HANDLE >( __readgsqword( o( 0x60 ) ) + o( 0x30 ) );
    }
}