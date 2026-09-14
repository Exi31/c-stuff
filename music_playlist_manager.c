
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Track {
    char *song_title;   // points to a string (pointer of the string in the heap, points to string stored in .rodata)
    char *artist;       // points to a string (...)
    int duration;       // in seconds
} Track;

typedef struct Playlist {   // OOP style
    // properties
    char *name;         // points to a string (...)
    Track *tracks;      // points to an array of track items on the heap
    int count;
    int capacity;

    // methods
    int (*add)(struct Playlist *, char *, char *, int);
    void (*view)(struct Playlist *);
    void (*free)(struct Playlist *);
} Playlist;

Playlist *create_playlist(char *name, int capacity) {
    Playlist *ptr = malloc(sizeof *ptr);
    if (ptr == NULL) {
        return NULL;
    }

    ptr->name = malloc(strlen(name) + 1);
    if (ptr->name == NULL) {
        free(ptr);
        return NULL;
    }
    strcpy(ptr->name, name);

    ptr->tracks = malloc(capacity * sizeof *ptr->tracks);
    if (ptr->tracks == NULL) {
        free(ptr->name);
        free(ptr);
        return NULL;
    }
    
    ptr->capacity = capacity;
    ptr->count = 0;

    

    return ptr;
}

int add_tracks(Playlist *ptr, char *song_title, char *artist, int duration) {
    if (ptr->count == ptr->capacity) {
        ptr->capacity *= 2;

        Track *temp = realloc(ptr->tracks, ptr->capacity * sizeof *ptr->tracks);
        if (temp == NULL) {
            ptr->capacity /= 2;
            return -1;
        }

        ptr->tracks = temp;
    }

    (ptr->tracks)[ptr->count].song_title = malloc(strlen(song_title) + 1);
    if ((ptr->tracks)[ptr->count].song_title == NULL) return -1;

    (ptr->tracks)[ptr->count].artist = malloc(strlen(artist) + 1);
    if ((ptr->tracks)[ptr->count].artist == NULL) {
        free((ptr->tracks)[ptr->count].song_title);
        return -1;
    }

    strcpy(((ptr->tracks)[ptr->count].song_title), song_title);
    strcpy(((ptr->tracks)[ptr->count].artist), artist);
    (ptr->tracks)[ptr->count].duration = duration;
    ptr->count++;

    return 0;
}

void free_playlist(Playlist *ptr) {
    for (int i = 0; i < ptr->count; i++) {
        free((ptr->tracks)[i].song_title);
        free((ptr->tracks)[i].artist);
    }

    free(ptr->name);
    free(ptr->tracks);
    free(ptr);
}

void view_playlist(Playlist *ptr) {
    printf("\n%s\n-----------------------------------------------------------------\n", ptr->name);

    for (int i = 0; i < ptr->count; i++) {
        printf("%d.\t%s - %s | %d:%02d\n", (i + 1), (ptr->tracks)[i].song_title, (ptr->tracks)[i].artist, ((ptr->tracks)[i].duration / 60), ((ptr->tracks)[i].duration % 60));
    }
}

int main(void) {
    Playlist *playlist_ptr = create_playlist("white girl music for gym rats", 2);

    playlist_ptr->add = add_tracks;
    playlist_ptr->view = view_playlist;
    playlist_ptr->free = free_playlist;

    if (playlist_ptr == NULL) {
        printf("Playlist creation failed (memory problems).\n");
        return 1;
    }

    while (true) {
        int n;
        printf("\nDo you want to add a track into your playlist? (1 for yes, 0 for no): ");
        scanf("%d", &n);
        while (getchar() != '\n');  // clear stdin buffer until the newline is consumed

        if (!n) break;
        else {
            char song_title[100], artist[100];
            int duration;

            printf("Song title: ");
            fgets(song_title, sizeof(song_title), stdin);
            song_title[strcspn(song_title, "\n")] = '\0'; // Strip trailing \n

            printf("Artist name: ");
            fgets(artist, sizeof(artist), stdin);
            artist[strcspn(song_title, "\n")] = '\0'; // Strip trailing \n

            printf("Duration (in seconds): ");
            scanf("%d", &duration);
            while (getchar() != '\n');  // clear leftover newline from scanf
            
            int flag = playlist_ptr->add(playlist_ptr, song_title, artist, duration);
            if (flag == -1) {
                printf("Track addition failed (memory problems).\n");
                playlist_ptr->free(playlist_ptr);
                playlist_ptr = NULL;
                return 1;
            } else if (flag == 0) {
                printf("\"%s\" added!\n", song_title);
            }
        }
    }

    playlist_ptr->view(playlist_ptr);
    playlist_ptr->free(playlist_ptr);
    playlist_ptr = NULL;
    return 0;
}