#include <stdio.h>
#include <string.h>

int main() {
    char a[10];

    printf("Enter a String : ");
    scanf("%s", a);

    int n = strlen(a);

    if (n < 2) {
        printf("String is invalid\n");
    } else if (n == 2) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 'b') {
                count++;
            }else{
                break;
            }
        }
        if (count == 2) {
            printf("String is valid\n");
        } else {
            printf("String is invalid\n");
        }
    }else{
        int count = 0;
        if(a[n-1] == 'b' && a[n-2]=='b'){
            for (int i = 0; i <= n-3; i++) {
                if (a[i] == 'a') {
                    count++;
                }else{
                    break;
                }
            }
            if (count == n-2) {
                printf("String is valid\n");
            } else {
                printf("String is invalid\n");
            }
        }else{
            printf("String is invalid\n");
        }
    }

    return 0;
}