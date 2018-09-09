/**
 *student: Samuel Desmond Kurtzer
 *ID:A1687068
 *student: Ryan James Faulkner
 *ID:A1707190
 *
 **/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct _process{
	char* ID;
	int init; //arrival time
	int age;
	int priority;
	int cpu;
	int numOfTimesServiced;
}process;

typedef struct _node{
	struct _node* next;
	struct _node* prev;
	process* data;
	//for accessability
	int priority;
}node;

process initProcess(char* ID, int init, int age, int priority, int cpu){
	process temp;
	temp.ID = ID;
	temp.init=init;
	temp.age=age;
	temp.priority=priority;
	temp.cpu=cpu;
	temp.numOfTimesServiced=0;
	return temp;
}

node initNode(process* d){
	node temp;
	temp.next=NULL;
	temp.data=d;
	temp.prev=NULL;
	temp.priority=d->priority;
	return temp;
}

typedef struct _ll{
	node* head;
	node* ageHead;
	node* ageTail;
	node* tail;
}ll;

ll initList(){
	ll temp;
	temp.head=NULL;
	temp.ageHead=NULL;
	temp.ageTail=NULL;
	temp.tail=NULL;
	return temp;
}

void add(ll* list, node* addee){
	if(list->head==NULL){
		list->head=addee;
	}else if(list->tail==NULL){
		list->tail=addee;
		list->tail->next=list->head;
		list->tail->prev=list->head;
		list->head->next=list->tail;
		list->head->prev=list->tail;
	}else{
		list->tail->next=addee;
		addee->next=list->head;
		addee->prev=list->tail;
		list->tail=addee;
	}
}

void rotate(ll* list){
	list->tail=list->head;
	list->head=list->head->next;
}

int isEmpty(ll* list){
	if(list->head==NULL)return true;
	return false;
}

process* removeNode(ll* list, node* toDelete){
	node* walker=list->head;
	process* ret;
	if(list->head==toDelete){
		list->head=list->head->next;
		list->tail->next=list->head;
		walker->next=NULL;
		ret=walker->data;
	}else if(list->tail==toDelete){
		node* next=list->tail->next;
		node* prev=list->tail->prev;
		next->prev=prev;
		prev->next=next;
		walker->next=NULL;
		walker->prev=NULL;
		ret=walker->data;
	}
	else{
		node* forwards=toDelete->next;
		node* backwards=toDelete->prev;
		forwards->prev=backwards;
		backwards->prev=forwards;
		walker->next=NULL;
		walker->prev=NULL;
		ret=walker->data;
	}
	return ret;
}


int main(int argc, char* argv[]){

	FILE *fp;
    fp = fopen("sample-input.txt", "r");
    process arr[60];
    char str[60];
    int tempArrival;
    int tempPriority;
    int tempAge;
    int tempRequired;
    char *tempName= (char *) malloc(60);
    int i = 0;
    while( fscanf (fp,"%s %d %d %d %d", tempName,&tempArrival,&tempPriority,&tempAge,&tempRequired)!= EOF ) 
    {
        arr[i] = initProcess(tempName,tempArrival,tempPriority,tempAge,tempRequired);
        tempName = (char *) malloc(60);
        i++;
    }
    fclose(fp);
    process tempProcess;
    for(int j = 1; j < i; j++)
    {
        for(int k = j; k > 0 ; k--)
        {
            if(arr[k].init < arr[k-1].init)
            {
                tempProcess = arr[k-1];
                arr[k-1] = arr[k];
                arr[k] = tempProcess;
            }
            else
            {
                break;
            }
        }
    }
	//queue init
	ll queue6=initList();
	ll queue5=initList();
	ll queue43=initList();
	ll queue21=initList();
	//
	//get code here
	int tick = arr[0].init;
	ll* currentList;
	switch(arr[0].priority){
		case 6:
			currentList = &queue6;
			break;
		case 5:
			currentList = &queue5;
			break;
		case 4:
		case 3:
			currentList = &queue43;
			break;
		case 2:
		case 1:
			currentList = &queue21;
			break;
		default:
			printf("invalid priority detected. please check initprocess and while(arr[currentNodeVal])");
		
	}
	int nextTimeToAdd=arr[0].init;
	int currentNodeVal=0;
	int ticksThisRun = 0;
	while(true){
		if(nextTimeToAdd==tick){
			//add new processes here
			while(arr[currentNodeVal].init==tick){
				node temp=initNode(&arr[currentNodeVal]);
				switch(temp.priority){
					case 6:
						add(&queue6, &temp);
						break;
					case 5:
						add(&queue5, &temp);
						break;
					case 4:
					case 3:
						add(&queue43, &temp);
						break;
					case 2:
					case 1:
						add(&queue21, &temp);
						break;
					default:
						printf("invalid priority detected. please check initprocess and while(arr[currentNodeVal])");
					
				}
				currentNodeVal++;
			}
			nextTimeToAdd = arr[currentNodeVal].init;
			//if currentNode in array is further in array than there were lines in input file, set timeToAdd as -1 so we never add another node, we reached end of the list
			if(currentNodeVal == i)
			{
				nextTimeToAdd = -1;
			}
			//this switch statement checks if higher queues which used to be empty had nodes added to them, and if so changes the current list and resets the ticksThisRun counter.
			//also moves the node which was being done to the back of it's own queue if it was in the middle of running
			if(currentList == &queue5 || currentList == &queue43 || currentList == &queue21)
			{
				if(currentList == &queue43 || currentList == &queue21)
				{

					if(currentList == &queue21)
					{
						if(isEmpty(&queue43))
						{
							if(ticksThisRun != 0)
							{
								rotate(currentList);
							}
							currentList = &queue43;
							ticksThisRun = 0;
						}
					}
					if(isEmpty(&queue5) == false)
					{
						if(ticksThisRun != 0)
						{
							rotate(currentList);
						}
						currentList = &queue5;
						ticksThisRun = 0;
					}
				}
				if(isEmpty(&queue6) == false)
				{
					if(ticksThisRun != 0)
					{
						rotate(currentList);
					}
					currentList = &queue6;
					ticksThisRun = 0;
				}
			}
		}
		//increment the current process.
		
		//check if the current process needs to be moved to the back of the line or demoted to another queue.
		//queue 1 runs are 5  ticks and priority is reduced
		//queue 2 runs are 10 ticks long and needs their priority reduced by one every 2 runs or 20 cycles.
		//queue 3 runs are 20 ticks
		//ageing section starts here
		if(runFinished){
			//age everything by 1
			node* walker=queue21.head;
			while(walker!=queue21.head){
				walker->data->age++;
				walker=walker->next;
				//also needs to check if age has gone over;
				if(walker->data->age>7){
					walker->priority++;
					walker->data->priority++;
					if(walker->priority>2){
						process* temp=removeNode(&queue21, walker);
						node newNode=initNode(temp);
						add(&queue43, &newNode);
					}
				}
			}
			walker=queue43.head;
			while(walker!=queue43.head){
				walker->data->age++;
				walker=walker->next;
				//also needs to check if age has gone over;
				if(walker->data->age>7){
					walker->priority++;
					walker->data->priority++;
					if(walker->priority>2){
						process* temp=removeNode(&queue43, walker);
						node newNode=initNode(temp);
						add(&queue5, &newNode);
					}
				}
			}
			//might have some problems here so printing a reminder
			printf("check while loops are running below if(runFinished)");
			runFinished=false;
		}
		//promote processes
		tick++;
	}
    return 0;
}