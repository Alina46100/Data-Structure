#include <stdio.h>

#define MAXN 1000100

int prefix[MAXN];
int N;
int K;

int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );
     
     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}


int main() {
    int input;
    int max=0;
    scanf("%d %d", &N, &K);
    int in[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &input);
        in[i] = input;
        
        if(max<input)  max=input;
    }
    int count = 0;
    int in_count = 0;
    qsort( in, N, sizeof(int), compare );
    //printf("%d\n ", max);
     for (int i = 0; i <= max; i++) {
        while(i==in[in_count] ){
            if(i>=K)
                count++;
            in_count++;
        }
        prefix[i]=count;
    }

    long long ans = 0;
    long long temp = 0;
    long long a=0;
    long long  b=0;

    for(int i=K ; i<=max ; i++){
        temp = 0;
        for(int j=0 ; j<=(max/i) ; j++){
            a=0;
            b=0;
            if( (i*(j+1)-1) >= 0)
                if((i*(j+1)-1) > max)
                    a = prefix[max];
                else
                    a = prefix[i*(j+1)-1];
            if( (i*j-1) >= 0 )
                if(i*j-1 > max)
                    b = prefix[max];
                else
                    b = prefix[i*j-1];
            temp = temp + (a-b)*i*j;
        }
        if(ans<temp)
            ans=temp;
    }

    printf("%lld\n", ans);

    return 0;
}