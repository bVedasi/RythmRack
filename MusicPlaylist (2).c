#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct songNode {
    int Sid;
    char song[100], artist[100];
    struct songNode *lptr, *rptr;
} songNode;

typedef struct list {
    int id;
    char playname[100];
    struct list *rlink, *llink;
    songNode *front, *rear;
} playlist;

playlist *start = NULL, *last = NULL;

void createPlaylist() {
    char sname[100], artname[100], pname[100];
    songNode *newsong;
    playlist *newnode;
    char ch;
    newnode = (playlist *)malloc(sizeof(playlist));
    newnode->llink = newnode->rlink = NULL;
    printf("Enter playlist name: ");
    scanf(" %99[^\n]", pname);
    strcpy(newnode->playname, pname);
    if (start == NULL) {
        newnode->id = 1;
        start = last = newnode;
    } else {
        newnode->id = last->id + 1;
        last->rlink = newnode;
        newnode->llink = last;
        last = newnode;
    }
    newnode->front = newnode->rear = NULL;
    while (1) {
        printf("Do you want to add a song?(Y or N)\n");
        scanf(" %c", &ch);  
        if (ch == 'Y' || ch == 'y') {
            newsong = (songNode *)malloc(sizeof(songNode));
            newsong->lptr = newsong->rptr = NULL;
            printf("Enter song name: ");
            scanf(" %99[^\n]", sname);
            printf("Enter artist name: ");
            scanf(" %99[^\n]", artname);
            strcpy(newsong->artist, artname);
            strcpy(newsong->song, sname);
            if (newnode->front == NULL) {
                newsong->Sid = 1;
                newnode->front = newnode->rear = newsong;
            } else {
                newsong->Sid = newnode->rear->Sid + 1;
                newnode->rear->rptr = newsong;
                newsong->lptr = newnode->rear;
                newnode->rear = newsong;
            }
        } else
            break;
    }
    last = newnode;
}

void displayLibrary() {
    playlist *temp = start;
    if (start != NULL) {
        printf("   S.NO   |  Playlist |\n");
        while (temp != NULL) {
            printf("    %d    |    %s     |\n", temp->id, temp->playname);
            temp = temp->rlink;
        }
    } else
        printf("Library is empty\n");
}

void playmusic(int ch, playlist *temp) {
    songNode *temp2 = temp->front;
    int num;
    if (ch == 1) {
        while (temp2 != NULL) {
            printf("  S.NO : %d  |  Song Name: %s  |  Artist Name: %s  |\n", temp2->Sid, temp2->song, temp2->artist);
            for (int i = 0; i < 10; ++i) {
                sleep(1);
                printf("  .");
                fflush(stdout); 
            }
            printf("\n"); 

            temp2 = temp2->rptr;
        }
    } 
    else if (ch == 2) {
        printf("Enter song number: ");
        scanf("%d", &num);
        while (temp2 != NULL && temp2->Sid != num) {
            temp2 = temp2->rptr;
        }
        if (temp2 != NULL) {
            printf("  S.NO : %d  |  Song Name: %s  |  Artist Name: %s  |\n", temp2->Sid, temp2->song, temp2->artist);
        } 
        else {
            printf("Song with S.NO %d not found.\n", num);
        }
    } 
    /*
    else if(ch==3){

    }
    */
    else if (ch == 4) {
        return;
    } 
    else {
        printf("Invalid Choice\n");
    }
}

void myLibrary() {
    char choice;
    int playch, sno;
    playlist *newnode = start;
    if (start == NULL) {
        printf("Your library is empty\n");
        printf("Do you want to create a new playlist? (Y or N)\n");
        scanf(" %c", &choice); 
        if (choice == 'Y' || choice == 'y')
            createPlaylist();
    } else {
        displayLibrary();
        printf("Do you want to create a new playlist? (Y or N)\n");
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
            createPlaylist();
        
        printf("Which playlist do you want to open? (Enter S.NO): ");
        scanf("%d", &sno);
        newnode = start;
        while (newnode != NULL && newnode->id != sno) {
            newnode = newnode->rlink;
        }
        if (newnode != NULL) {
            printf("    %d    |    %s     |\n", newnode->id, newnode->playname);
            while(1){
                printf("\n1. Play music\n2. Edit Songs\n3. Delete song\n4. Add song\n5. Exit Playlist\n");
                printf("Enter your choice: ");
                scanf("%d", &playch);
                switch (playch) {
                    case 1:
                        printf("\n1. Start Playing from top\n2. Play a song\n3. Shuffle\n4. Exit playlist\n");
                        printf("Enter your choice: ");
                        scanf("%d", &playch);
                        playmusic(playch, newnode);
                        break;
                    /*
                    case 2:
                        // Edit songs code
                        break;
                    case 3:
                        // Delete song code
                        break;
                    case 4:
                        // Add song code
                        break;
                    */
                    case 5:
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
                if(playch==5)
                    break;
            }
        } 
        else {
            printf("Playlist with S.NO %d not found.\n", sno);
        }
    }
}

int main() {
    int ch;
    printf("MUSIC PLAYLIST\n\n");
    while (1) {
        printf("1. My Library\n2. Home\n3. Search\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                myLibrary();
                break;
            case 2:
                // home();
                break;
            case 3:
                // search();
                break;
            case 4:
                exit(0);
            default:
                printf("Enter valid choice\n");
        }
    }
    return 0;
}
