#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; i++) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames, pages, pageFaults = 0, counter = 0, pos;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter the number of pages: ");
    scanf("%d", &pages);
    
    int pageSequence[pages], frame[frames], time[frames];
    
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
                counter++;
                time[j] = counter;
                break;
            }
        }

        if (!found) {
            if (pageFaults < frames) {
                frame[pageFaults] = pageSequence[i];
                counter++;
                time[pageFaults] = counter;
                pageFaults++;
            } else {
                pos = findLRU(time, frames);
                frame[pos] = pageSequence[i];
                counter++;
                time[pos] = counter;
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
