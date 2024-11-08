#include <stdio.h>

void initializeFrames(int frame[], int frames);
int isPageInFrame(int frame[], int frames, int page);
void printFrames(int frame[], int frames);
int replacePageFIFO(int frame[], int frames, int page, int *pointer);


void initializeFrames(int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }
}

int isPageInFrame(int frame[], int frames, int page) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == page) {
            return 1;
        }
    }
    return 0;
}

void printFrames(int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frame[i]);
        }
    }
    printf("\n");
}

int replacePageFIFO(int frame[], int frames, int page, int *pointer) {
    frame[*pointer] = page;
    *pointer = (*pointer + 1) % frames;
    return 1;
}


int main() {
    int frames, pages, pageFaults = 0, pointer = 0;
    
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter the number of pages: ");
    scanf("%d", &pages);
    
    int pageSequence[pages], frame[frames];
    
    printf("Enter the page sequence: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &pageSequence[i]);
    }

    initializeFrames(frame, frames);

    printf("\nPage replacement process:\n");

    for (int i = 0; i < pages; i++) {
        int page = pageSequence[i];

        if (!isPageInFrame(frame, frames, page)) {
            pageFaults += replacePageFIFO(frame, frames, page, &pointer);
        }

        printf("Page %d -> ", page);
        printFrames(frame, frames);
    }

    printf("\nTotal page faults: %d\n", pageFaults);

    return 0;
}