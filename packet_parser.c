
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Packet {
    char *header;
    char *payload;
    int *checksums;
    size_t checksum_count;
} Packet;

Packet *create_packet(const char *hdr, const char *data, const int *checks, size_t count) {
    Packet *ptr = malloc(sizeof *ptr);
    if (ptr == NULL) return NULL;

    ptr->header = NULL;
    ptr->payload = NULL;
    ptr->checksums = NULL;

    ptr->header = malloc(strlen(hdr) + 1);
    if (ptr->header == NULL) goto cleanup;

    ptr->payload = malloc(strlen(data) + 1);
    if (ptr->payload == NULL) goto cleanup;

    ptr->checksums = malloc(count * sizeof(int));
    if (ptr->checksums == NULL) goto cleanup;

    strcpy(ptr->header, hdr);
    strcpy(ptr->payload, data);
    memcpy(ptr->checksums, checks, count * sizeof(int));
    ptr->checksum_count = count;

    return ptr;

cleanup:
    free(ptr->checksums);
    free(ptr->payload);
    free(ptr->header);
    free(ptr);
    return NULL;
}

void destroy_packet(Packet *pkt) {
    free(pkt->header);
    free(pkt->payload);
    free(pkt->checksums);
    free(pkt);
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    Packet *packet_ptr = create_packet("con cac", "dau buoi", arr, 5);

    if (packet_ptr == NULL) {
        printf("Packet creation failed.\n");
        return 1;
    }

    printf("%s\n%s\n", packet_ptr->header, packet_ptr->payload);

    for (size_t i = 0; i < packet_ptr->checksum_count; i++) {
        printf("%d ", packet_ptr->checksums[i]);
    }

    printf("\nChecksum count: %zu\n", packet_ptr->checksum_count);

    destroy_packet(packet_ptr);
    packet_ptr = NULL;

    return 0;
}