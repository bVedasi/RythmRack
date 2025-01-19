#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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

playlist *start=NULL, *last=NULL;

songNode *HomeHead=NULL,*HomeTail=NULL;

int total_songs=40;

void HomeSongs(){
    songNode *newSong;
    char *songNames[40]={
        "Perfect", "See You Again", "Sorry", "Blank Space", "Roar","Diamonds", "Animals", "What Makes You Beautiful", "Summer", "Burn",
        "Paradise", "Blinding Lights", "Hey Jude", "Circles", "Rolling in the Deep","Levitating", "Old Town Road", "God's Plan", "Happy", "Dynamite",
        "Radioactive", "Anaconda", "Treat You Better", "We Don't Talk Anymore", "Work","The Lazy Song", "Worth It", "Baby", "Shake It Off", "Side to Side",
        "Firework", "The Hills", "Thinking Out Loud", "Chandelier", "Counting Stars","Sugar", "Hello", "Faded", "Closer", "You're Beautiful"};
    char *artistNames[40]={
        "Ed Sheeran", "Wiz Khalifa ft. Charlie Puth", "Justin Bieber", "Taylor Swift", "Katy Perry","Rihanna", "Martin Garrix", "One Direction", "Calvin Harris", "Ellie Goulding",
        "Coldplay", "The Weeknd", "The Beatles", "Post Malone", "Adele","Dua Lipa", "Lil Nas X ft. Billy Ray Cyrus", "Drake", "Pharrell Williams", "BTS",
        "Imagine Dragons", "Nicki Minaj", "Shawn Mendes", "Charlie Puth ft. Selena Gomez", "Rihanna ft. Drake","Bruno Mars", "Fifth Harmony ft. Kid Ink", "Justin Bieber ft. Ludacris", "Taylor Swift", "Ariana Grande ft. Nicki Minaj",
        "Katy Perry", "The Weeknd", "Ed Sheeran", "Sia", "OneRepublic","Maroon 5", "Adele", "Alan Walker", "The Chainsmokers ft. Halsey", "James Blunt"};

    for(int i=0;i<40;i++){
        newSong=(songNode*)malloc(sizeof(songNode));
        newSong->Sid=i+1;
        strcpy(newSong->song,songNames[i]);
        strcpy(newSong->artist,artistNames[i]);
        newSong->lptr =NULL;
        newSong->rptr =NULL;
        if (HomeTail!=NULL)
            HomeTail->rptr=newSong;
        else
            HomeHead=newSong;
        HomeTail = newSong;
    }
}

void add_to_home()
{
    char art[30],sing[30];
    songNode *newsong;
    newsong=(songNode *)malloc(sizeof(songNode));
    printf("Enter Name of song: ");
    scanf(" %[^\n]",&sing);
    printf("\nEnter Name of Artist: ");
    scanf(" %[^\n]",&art);
    strcpy(newsong->artist,art);
    strcpy(newsong->song,sing);
    newsong->Sid=total_songs+1;
    total_songs++;
    printf("\n");
    HomeTail->rptr=newsong;
    newsong->lptr=HomeTail;
    HomeTail=newsong;
    HomeTail->rptr=NULL;
}

void displayHomeSongs() {
    songNode *temp=HomeHead;
    printf("Home Songs:\n");
    printf("  S.NO | Song Name                 | Artist Name                    |\n");
    printf("---------------------------------------------------------------------\n");
    while(temp!=NULL) {
        printf("  %3d  | %-25s | %-30s |\n", temp->Sid, temp->song, temp->artist);
        temp=temp->rptr;
    }
}

void displayPlaylist(playlist *mnode){
    songNode *temp=mnode->front;
    if(mnode->front!=NULL){
        while(temp!=NULL){
            printf("  S.NO : %d  |  Song Name: %-25s  |  Artist Name: %-25s  |\n", temp->Sid, temp->song, temp->artist);
            temp=temp->rptr;
        }       
    }
    else
        printf("Playlist is empty\n");
}

playlist* shuffle(playlist *temp1){
    int count=0;
    songNode *traverse=temp1->front;
    while(traverse !=NULL) {
        count++;
        traverse=traverse->rptr;
    }

    int selected[count];

    for(int i=0;i<count;i++) {
        selected[i]=0;
    }

    songNode *f=NULL, *r=NULL;
    traverse=temp1->front;

    while(traverse!=NULL) {
        int random_num;
        do {
            random_num=rand() % count;
        } while(selected[random_num]);

        selected[random_num]=1;

        songNode *temp2=temp1->front;
        for(int p=0; p < random_num; p++) {
            temp2=temp2->rptr;
        }

        songNode *naya=(songNode *)malloc(sizeof(songNode));
        if(naya==NULL) {
            free(selected);
            return NULL;
        }
        naya->Sid=temp2->Sid;
        strcpy(naya->artist, temp2->artist);
        strcpy(naya->song, temp2->song);
        naya->rptr=NULL;
        naya->lptr=r;

        if(f==NULL) {
            f=naya;
            r=naya;
        } else {
            r->rptr=naya;
            naya->lptr=r;
            r=naya;
        }

        traverse=traverse->rptr;
    }

    free(selected);

    temp1->front=f;
    temp1->rear=r;

    while(traverse !=NULL) {
        songNode *temp3=traverse;
        traverse=traverse->rptr;
        free(temp3);
    }

    return temp1;
}

void addSong(playlist *mnode){
    char songname[100], artistname[100],ch;
    songNode *newsong,*temp=HomeHead;
    int flag=0;
    printf("Enter song name: ");
    scanf(" %[^\n]s",songname);
    printf("Enter artist name: ");
    scanf(" %[^\n]s",artistname);
    while(temp!=NULL){
        if(strcasecmp(temp->song,songname)==0 && strcasecmp(temp->artist,artistname)==0){
            flag=1;
            break;
        }
        temp=temp->rptr;
    }
    if(flag==1){
        newsong=(songNode*)malloc(sizeof(songNode));
        if(mnode->rear!=NULL)
            newsong->Sid=mnode->rear->Sid+1;
        else
            newsong->Sid=1;
        strcpy(newsong->song,temp->song);
        strcpy(newsong->artist,temp->artist);
        newsong->lptr=NULL;
        newsong->rptr=NULL;
        if (mnode->rear==NULL) 
            mnode->front=newsong;
        else 
            mnode->rear->rptr=newsong;    
        mnode->rear=newsong;
        displayPlaylist(mnode);
    }
    else {
        printf("Song is not available\n");
    }
}

void createPlaylist() {
    char sname[100], artname[100], pname[100];
    songNode *newsong;
    playlist *newnode;
    char ch;
    newnode=(playlist *)malloc(sizeof(playlist));
    newnode->llink=newnode->rlink=NULL;
    printf("Enter playlist name: ");
    scanf(" %99[^\n]", pname);
    strcpy(newnode->playname, pname);
    if (start==NULL) {
        newnode->id=1;
        start=last=newnode;
    } else {
        newnode->id=last->id + 1;
        last->rlink=newnode;
        newnode->llink=last;
        last=newnode;
    }
    newnode->front=newnode->rear=NULL;
    while (1) {
        printf("Do you want to add a song?(Y or N)\n");
        scanf(" %c", &ch);  
        if (ch=='Y' || ch=='y') {
            addSong(newnode);
       } 
       else
            break;
    }
    last=newnode;
}

void displayLibrary() {
    playlist *temp=start;
    if (start !=NULL) {
        printf("   S.NO   |  Playlist |\n");
        while (temp !=NULL) {
            printf("    %d    |    %s     |\n", temp->id, temp->playname);
            temp=temp->rlink;
        }
    } else
        printf("Library is empty\n");
}

void playmusic(int ch, playlist *temp) {
    songNode *temp2=temp->front;
    int num;
    if (ch==1) {
        while (temp2 !=NULL) {
            printf("  S.NO : %d  |  Song Name: %s  |  Artist Name: %s  |\n", temp2->Sid, temp2->song, temp2->artist);
            for (int i=0; i < 10; ++i) {
                sleep(1);
                printf("  .");
                fflush(stdout); 
            }
            printf("\n"); 
            temp2=temp2->rptr;
        }
    } 
    else if (ch==2) {
        displayPlaylist(temp);
        printf("Enter song number: ");
        scanf("%d", &num);
        while (temp2 !=NULL && temp2->Sid !=num) {
            temp2=temp2->rptr;
        }
        if (temp2 !=NULL) {
            printf("  S.NO : %d  |  Song Name: %-25s  |  Artist Name: %-25s  |\n", temp2->Sid, temp2->song, temp2->artist);
            for (int i=0; i < 10; ++i) {
                sleep(1);
                printf("  .");
                fflush(stdout); 
            }
        } 
        else {
            printf("Song with S.NO %d not found.\n", num);
        }
    } 
    else if(ch==3){
        shuffle(temp);
    }
    else if (ch==4) {
        return;
    } 
    else {
        printf("Invalid Choice\n");
    }
}

void myLibrary() {
    char choice;
    int sno,choic;
    if (start==NULL) {
        printf("Your library is empty\n");
        printf("Do you want to create a new playlist? (Y or N)\n");
        scanf(" %c", &choice); 
        if (choice=='Y' || choice=='y')
            createPlaylist();
    } else {
        displayLibrary();
        printf("1. Create New Playlist\n2. Open a Playlist\nEnter your Choice: ");
        scanf("%d",&choic);
        switch(choic){
            case 1:
                createPlaylist();
                break;
            case 2:
                openplaylist();
                break;
        }
    }
}

void openplaylist()
{
    int sno;
    playlist *newnode=start;
    songNode *temp;
    int playch;
    printf("Which playlist do you want to open? (Enter S.NO): ");
    scanf("%d", &sno);
    newnode=start;
    while (newnode !=NULL && newnode->id !=sno) {
        newnode=newnode->rlink;
    }
    if (newnode !=NULL) {
        printf("    %d    |    %s     |\n", newnode->id, newnode->playname);
        displayPlaylist(newnode);
        while(1){
            printf("\n1. Play music\n2. Add song\n3. Delete song\n4. Shuffle songs\n5. Exit Playlist\n");
            printf("Enter your choice: ");
            scanf("%d", &playch);
            switch (playch) {
                case 1:
                    printf("\n1. Start Playing from top\n2. Play a song\n3. Shuffle\n4. Exit playlist\n");
                    printf("Enter your choice: ");
                    scanf("%d", &playch);
                    playmusic(playch, newnode);
                    break;
                case 2:
                    addSong(newnode);
                    break;
                case 3:
                    if(newnode->front==NULL){
                        printf("No songs in playlist\n");
                    }
                    else{
                        displayPlaylist(newnode);
                        printf("Which song do you want to delete (Enter S.NO): ");
                        scanf("%d",&sno);
                        temp=newnode->front;
                        if(temp->Sid==sno){
                            if(newnode->front!=newnode->rear){
                                newnode->front=temp->rptr;
                                newnode->front->lptr=NULL;
                                free(temp);
                            }
                            else{
                                newnode->front=newnode->rear=NULL;
                                free(temp);
                            }
                        }
                        else{
                            songNode *prev=temp;
                            temp=temp->rptr;
                            while(temp->Sid!=sno && temp!=NULL){
                                prev=temp;
                                temp=temp->rptr;
                            }
                            if(temp->Sid==sno && temp->rptr!=NULL){
                                temp->rptr->lptr=prev;
                                prev->rptr=temp->rptr;
                                free(temp);
                            }
                            else if(temp->rptr==NULL && temp->Sid==sno){
                                newnode->rear=temp->lptr;
                                prev->rptr=NULL;
                                free(temp);
                            }
                            else{
                                printf("Enter a correct choice\n");
                            }
                        }
                    }
                    if(newnode->front!=NULL){
                        temp=newnode->front;
                        temp->Sid=1;
                        temp=temp->rptr;
                        while (temp!=NULL) {
                            temp->Sid=temp->lptr->Sid+1;
                            temp=temp->rptr;
                        }
                    }
                    break;
                case 4:
                    newnode=shuffle(newnode);
                    int num=1;
                    songNode *tempo=newnode->front;
                    while(tempo!=NULL)
                    {
                        tempo->Sid=num;
                        num++;
                        tempo=tempo->rptr;
                    }
                    displayPlaylist(newnode);
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid choice\n");
                    break;
            }
        }
    }
    else 
        printf("Playlist with S.NO %d not found.\n", sno);
}

void sort(playlist *temp){
    songNode*temp1;
    char sortart[100];
    temp1=temp->front;
    displayPlaylist(temp);
    printf("Enter name of the artist to sort by: ");
    scanf(" %[^\n]",&sortart);
    while(temp1!=NULL){
        if(temp1->artist==sortart)
            printf("  S.NO : %d  |  Song Name: %-25s  |  Artist Name: %-25s  |\n", temp1->Sid, temp1->song, temp1->artist);
        temp1=temp1->rptr;
    }
}

void search(){
    songNode *temp;
    int cho;
    temp=HomeHead;
    emo:
    printf("1. Search By Artist\n2. Search By Song Name\nEnter Choice: ");
    scanf("%d",&cho);
    if (cho==1)
        printf("Enter the artist name: ");
    else 
        printf("Enter the song name: ");
    char scanned[100];
    scanf(" %[^\n]",&scanned);
    if(cho==1)
    {
        while(temp!=NULL)
        {
            if(strcmp(scanned,temp->artist)==0)
            {
                printf("  S.NO : %d  |  Song Name: %s  |  Artist Name: %s  |\n", temp->Sid, temp->song, temp->artist);
                break;
            }
            else 
                temp=temp->rptr;
        }
        if(temp==NULL)
            printf("No songs by %s\n",scanned);
    }
    else if(cho==2)
    {
        while(temp!=NULL)
        {
            if(strcmp(scanned,temp->song)==0)
            {
                printf("  S.NO : %d  |  Song Name: %s  |  Artist Name: %s  |\n", temp->Sid, temp->song, temp->artist);
                break;
            }
            else 
                temp=temp->rptr;
        }
        if(temp==NULL)
            printf("No songs by the name %s\n",scanned);
    }
    else 
    {
        printf("Enter Valid choice\n");
        goto emo;
    }
}



int main() {
    int ch;
    int taken;
    printf("MUSIC PLAYLIST\n\n");
    HomeSongs();
    while (1) {
        printf("1. Home\n2. My Library\n3. Search\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                abc:
                printf("1. Display Home Songs\n2. Add to Home Songs\nEnter Your Choice: ");
                scanf("%d",&taken);
                if(taken==1)
                    displayHomeSongs();
                else if(taken==2)
                    add_to_home();
                else{
                    printf("Enter a correct choice\n");
                    goto abc;
                }
                break;
            case 2:
                myLibrary();
                break;
            case 3:
                search();
                break;
            case 4:
                exit(0);
            default:
                printf("Enter valid choice\n");
        }
    }
    return 0;
}