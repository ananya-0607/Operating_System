#include<stdio.h>

int FIFO(int pages[],int n,int frame_size);
int LRU(int pages[],int n,int frame_size);
int MRU(int pages[],int n,int frame_size);

int FIFO(int pages[],int n,int frame_size)
{
    int pagesfault=0;
    int index=0;
    int frame[frame_size];

    for(int i=0;i<n;i++)
    {
        int pagefound=0;
        for(int j=0;j<frame_size;j++)
        {
            if(frame[j]==pages[i])
            {
                pagefound=1;
                break;
            }
        }
        
        if(pagefound==0)
        {
            frame[index]=pages[i];
            index=((index+1)%frame_size);
            pagesfault++;
        }

    }
    return pagesfault;
}

int LRU(int pages[],int n,int frame_size)
{
    int pagesfault=0;
    int frame[frame_size];
    int recent[frame_size];
    int framecount=0;
    int minindex;

    for(int i=0;i<frame_size;i++)
    {
        frame[i]=-1;
        recent[i]=-1;
    }

    for(int i=0;i<n;i++)
    {
        int pagefound=0;
        for(int j=0;j<frame_size;j++)
        {
            if(frame[j]==pages[i])
            {
                recent[j]=i;
                pagefound=1;
                break;
            }
        }
        if(pagefound==0)
        {
            if(framecount<frame_size)
            {
                recent[framecount]=i;
                frame[framecount]=pages[i];
                framecount++;
            }
            else
            {
                minindex=0;
                for(int k=0;k<frame_size;k++)
                {
                    if(recent[k]<recent[minindex])
                    {
                        minindex=k;
                    }
                }
                frame[minindex]=pages[i];
                recent[minindex]=i;
            }
            pagesfault++;
        }
    }
    return pagesfault;
}

int MRU(int pages[],int n,int frame_size)
{
    int frame[frame_size];
    int recent[frame_size];
    int pagefault=0;
    int max_index;
    int framecount=0;

    for(int i=0;i<frame_size;i++)
    {
        recent[i]=-1;
        frame[i]=-1;
    }
    for(int i=0;i<n;i++)
    {
        int pagefound=0;
        for(int j=0;j<frame_size;j++)
        {
            if(pages[i]==frame[j])
            {
                recent[j]=i;
                pagefound=1;
                break;
            }
        }
        if(pagefound==0)
        {
            if(framecount<frame_size)
            {
                frame[framecount]=pages[i];
                recent[framecount]=i;
                framecount++;
            }
            else
            {
                max_index=0;
                for(int k=0;k<frame_size;k++)
                {
                    if(recent[k]>recent[max_index])
                    {
                        max_index=k;
                    }
                }
                frame[max_index]=pages[i];
                recent[max_index]=i;
            }
            pagefault++;
        }
    }
    return pagefault;
}

int Optimal(int pages[],int n,int frame_size)
{
    int frame[frame_size];
    int pagefault=0;
    int framecount=0;

    for(int i=0;i<n;i++)
    {
        int pagefound=0;
        for(int j=0;j<frame_size;j++)
        {
            if(pages[i]==frame[j])
            {
                pagefound=1;
                break;
            }
        }

        if(pagefound==0)
        {
            if(framecount<frame_size)
            {
                frame[framecount]=pages[i];
                framecount++;
            }
            else
            {
                int fardhest=i;
                int index=-1;
                for(int k=0;k<frame_size;k++)
                {
                    int next=i+1;
                    while(next<n && pages[next]!=frame[k])
                    {
                        next++;
                    }
                    if(next>fardhest)
                    {
                        fardhest=next;
                        index=k;
                    }
                }
                if(index==-1)
                {
                    index=0;
                }
                frame[index]=pages[i];
            }
            pagefault++;
        }
    }
    return pagefault;
}

int main()
{
    int pages[] = {6, 1, 1, 2, 0, 3, 4, 6, 0, 2, 1, 2, 1, 2, 0, 3, 2, 1, 2, 0};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 4;
    printf("Number of Page Faults for FIFO: %d\n", FIFO(pages, n, frames));
    printf("Number of Page Faults for LRU: %d\n", LRU(pages, n, frames));
    printf("Number of Page Faults for Optimal: %d\n",Optimal(pages, n, frames));
    printf("Number of Page Faults for MRU: %d\n",MRU(pages, n, frames));
    return 0;
}