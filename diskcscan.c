#include <stdio.h>
#include <stdlib.h>

void cscan_disk_scheduling(int requests[], int n, int head, int disk_size)
{
    int total_head_movement = 0;
    int current_position = head;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (requests[i] > requests[j])
            {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    printf("C-SCAN Disk Scheduling:\n");
    printf("Order of processing: %d -> ", head);

    int index;

    for (index = 0; index < n; index++)
    {
        if (requests[index] >= head)
        {
            break;
        }
    }

    for (int i = index; i < n; i++)
    {
        total_head_movement += abs(current_position - requests[i]);
        current_position = requests[i];
        printf("%d -> ", requests[i]);
    }

    if (current_position != disk_size - 1)
    {
        total_head_movement += abs(current_position - (disk_size - 1));
        current_position = disk_size - 1;
        printf("%d -> ", current_position);
    }

    total_head_movement += disk_size - 1;
    current_position = 0;
    printf("%d -> ", current_position);

    for (int i = 0; i < index; i++)
    {
        total_head_movement += abs(current_position - requests[i]);
        current_position = requests[i];
        printf("%d", requests[i]);
        if (i < index - 1)
            printf(" -> ");
    }

    printf("\nTotal head movement: %d\n", total_head_movement);
}

int main()
{
    int n, head, disk_size;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the total disk size: ");
    scanf("%d", &disk_size);

    cscan_disk_scheduling(requests, n, head, disk_size);

    return 0;
}
