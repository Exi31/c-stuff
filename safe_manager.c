
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int session_id;
    char privilege_level;
} UserSession;

int safe_allocate(UserSession **out_session, int id, char privilege) {
    *out_session = malloc(sizeof(**out_session));        // not sure of the sizeof(**out_session), i just checked the use of sizeof(*p) but if we only deference once, the sizeof will still be 8 bytes of a pointer
    if (out_session == NULL) {
        printf("Allocation failed.\n");
        return -1;
    }

    (**out_session).session_id = id;
    (**out_session).privilege_level = privilege;

    return 0;
}

void safe_free_session(UserSession **session_ptr) {
    if (session_ptr != NULL && *session_ptr != NULL) {
        free(*session_ptr);
        *session_ptr = NULL;
    }
}

int main(void) {
    UserSession *my_session = NULL;

    int status = safe_allocate(&my_session, 1337, 'A');
    if (status != 0) printf("Quit.\n");

    printf("my_session's heap address: %p\n", my_session);

    safe_free_session(&my_session);
    printf("my_session's heap address: %p\n", my_session);

    return 0;
}