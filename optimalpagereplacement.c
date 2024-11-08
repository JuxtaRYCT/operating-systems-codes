#include <stdio.h>

int findOptimal(int pageSequence[], int frame[], int pages, int frames, int currentIndex) {
    int farthest = currentIndex, pos = -1;
    for (int i = 0; i < frames; i++) {
        int j;
        for (j = currentIndex; j < pages; j++) {
            if (frame[i] == pageSequence[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == pages) {
            return i;
        }
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames, pages, pageFaults = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter the number of pages: ");
    scanf("%d", &pages);
    
    int pageSequence[pages], frame[frames];
    
    printf("Enter the page sequence: ");
    for (int i = 0; i < pages; i++) {
        scanf("%d", &pageSequence[i]);
    }

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    printf("\nPage replacement process:\n");

    for (int i = 0; i < pages; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pageSequence[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            if (pageFaults < frames) {
                frame[pageFaults] = pageSequence[i];
                pageFaults++;
            } else {
                int pos = findOptimal(pageSequence, frame, pages, frames, i + 1);
                frame[pos] = pageSequence[i];
                pageFaults++;
            }
        }

        printf("Page %d -> ", pageSequence[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] == -1) {
                printf("- ");
            } else {
                printf("%d ", frame[j]);
            }
        }
        printf("\n");
    }

    printf("\nTotal page faults: %d\n", pageFaults);

    return 0;
}
