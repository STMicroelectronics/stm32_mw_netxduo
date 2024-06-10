#include "tls_test_frame.h"

extern TLS_TEST_SEMAPHORE* semaphore_echo_server_prepared;

/* Openssl echo server entry. */
INT openssl_echo_server_entry(TLS_TEST_INSTANCE* instance_ptr)
{

#if !defined(NX_SECURE_TLS_CLIENT_DISABLED) && (NX_SECURE_TLS_TLS_1_3_ENABLED) && defined(NX_SECURE_ENABLE_PSK_CIPHERSUITES)


INT status, exit_status;

/* Added -rev option to send reverse text received from clients back to the client. Added -naccept 1 to close the server after one tls session. */
CHAR* external_cmd[] = { "openssl-1.1", "s_server", "-rev", 
                         "-nocert",
                         "-psk", "112233445566",
                         "-psk_identity", "psk_test",
                         "-naccept", "1", (CHAR*)NULL};

    /* Post the semaphore to notify that the reverse echo server is prepared. */
    tls_test_semaphore_post(semaphore_echo_server_prepared);

    /* Launch the openssl server. */
    tls_test_launch_external_test_process(&exit_status, external_cmd);

#if 0 /* openssl exit with 0 no matter TLS session is established or not. */
    /* Check for the exit status of external program. */
    return_value_if_fail(0 == exit_status, TLS_TEST_INSTANCE_EXTERNAL_PROGRAM_FAILED);
#endif
    return TLS_TEST_SUCCESS;

#else

    return TLS_TEST_NOT_AVAILABLE;

#endif

}
