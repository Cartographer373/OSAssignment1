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
	int cpuOriginal;
	int numOfTimesServiced;
	int endTime;
	int readyTime;
}process;

typedef struct _node{
	struct _node* next;
	struct _node* prev;
	process* data;
	//for accessability
}node;

process initProcess(char* ID, int init, int priority, int age, int cpu){
	process temp;
	temp.ID = ID;
	temp.init=init;
	temp.age=age;
	temp.priority=priority;
	temp.cpu=cpu;
	temp.cpuOriginal = cpu;
	temp.numOfTimesServiced=0;
	temp.endTime = -1;
	temp.readyTime = -1;
	return temp;
}

node initNode(process* d){
	node temp;
	temp.next=NULL;
	temp.data=d;
	temp.prev=NULL;
	return temp;
}

typedef struct _ll{
	node* head;
	node* tail;
}ll;

ll initList(){
	ll temp;
	temp.head=NULL;
	temp.tail=NULL;
	return temp;
}

void add(ll* list, node* addee){
	printf("adding node: %s to %d\n",addee->data->ID,list);
	printf("adding node with priority: %d\n",addee->data->priority);

	if(list->tail != NULL){printf("tail is %s",list->tail->data->ID);}
	else printf("TAIL IS NULL");
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
		list->head->prev=addee;
		addee->next=list->head;
		addee->prev=list->tail;
		list->tail=addee;
	}
	printf("NEW HEAD IS %s", list->head->data->ID);
	printf("added \n");
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
	printf("REMOVING %s -----------FROM %d-----------------------------------------------------------------------------------------------------------", toDelete->data->ID,list);
	if(list->head==toDelete){
		list->head->next->previous=tail;
		list->tail->next=list->head->next;
		head->
	}else if(list->tail==toDelete){

	}
	printf("returning %s", ret->ID);
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
    for(int j = 0; j< i-1; j++)
    {
    	int minPos = j;
    	for(int k = j+1;k<i; k++)
    	{
    		if(arr[k].init < arr[minPos].init)
    		{
    			minPos = k;
    		}
    	}
    	tempProcess = arr[minPos];
    	arr[minPos] = arr[j];
    	arr[j] = tempProcess;
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
		    printf("priority is %d/n", arr[0].priority);
			printf("invalid priority detected. please check initprocess and while(arr[currentNodeVal])");
			return 0;

	}
	node nodeArr [60];
	node graveyard[60];
	for(int x = 0; x < i; x++)
	{
		nodeArr[x] = initNode(&arr[x]);
	} 
	int nextTimeToAdd=arr[0].init;
	int currentNodeVal=0;
	int ticksThisRun = 0;
	int runFinished = false;
	int skeletons = 0;
	//skeletons is number of processes that have "died", once all processes have finished loop ends
	while(skeletons < i){
		if(tick == 200)
		{
			return 0;
		}

		if(ticksThisRun == 5 && (currentList == &queue5 || currentList == &queue6))
		{
			runFinished = true;
			currentList->head->data->numOfTimesServiced++;
		}
		else if(ticksThisRun == 10 && (currentList == &queue43))
		{
			runFinished = true;
			currentList->head->data->numOfTimesServiced++;
		}
		else if(ticksThisRun == 20 && (currentList == &queue21))
		{
			runFinished = true;
			currentList->head->data->numOfTimesServiced++;
		}
		if(currentList != NULL)
		{
			if(currentList->head != NULL)
			{
				if(currentList->head->data->cpu == 0)
				{
					printf("hereS@S@@WW@");
					ticksThisRun = 0;
					currentList->head->data->endTime = tick;
					graveyard[skeletons] = initNode(currentList->head->data);
					skeletons++;
					if(currentList->head->next != NULL)
					{
						removeNode(currentList, currentList->head);
					}
					else
					{
						*currentList = initList();
						if(isEmpty(&queue6) != true)
						{
							currentList = &queue6;
						}
						else if(isEmpty(&queue5) != true)
						{
							currentList = &queue5;
						}
						else if(isEmpty(&queue43) != true)
						{
							currentList = &queue43;
						}
						else if(isEmpty(&queue21) != true)
						{
							currentList = &queue21;
						}
						else
						{
							printf("THJIS SHOULD NOT BE TRIGGERING, ALL LISTS ARE EMPTY \n");
							printf("THIS MANY CUSTOMERS HAVE ARRIVED  %d,\n",currentNodeVal);
							printf("THIS MANY CUSTOMERS HAVE LEFT  %d,\n",skeletons);

							currentList = NULL;
						}
					}
				}
			}
		}	
		if(nextTimeToAdd==tick){
			//add new processes here
			while(nodeArr[currentNodeVal].data->init==tick){
				switch(nodeArr[currentNodeVal].data->priority){
					case 6:
						add(&queue6, &nodeArr[currentNodeVal]);
						break;
					case 5:
						add(&queue5, &nodeArr[currentNodeVal]);

						break;
					case 4:
					case 3:
						add(&queue43, &nodeArr[currentNodeVal]);
						break;
					case 2:
					case 1:
						add(&queue21, &nodeArr[currentNodeVal]);
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
			//preemption code
			//this switch statement checks if higher queues which used to be empty had nodes added to them, and if so changes the current list and resets the ticksThisRun counter.
			//also moves the node which was being done to the back of it's own queue if it was in the middle of running
			if(currentList == &queue5 || currentList == &queue43 || currentList == &queue21)
			{
				if(currentList == &queue43 || currentList == &queue21)
				{

					if(currentList == &queue21)
					{
						if(isEmpty(&queue43) == false)
						{
							if(ticksThisRun != 0)
							{
								//if a run has finished and ticksThisRun is not 0 then we haven't deleted it yet and need to decrease priority before rotation if it is 2 (can't go below 1)
								//no need to check if it's dropped to a lower queue, already in lowest
								if(runFinished == true && (currentList->head->data->numOfTimesServiced==5 && (currentList==&queue6||currentList==&queue5)) || (currentList->head->data->numOfTimesServiced==2 && (currentList==&queue43)) && currentList->head->data->priority == 2)
								{
									currentList->head->data->priority--;
								}
								rotate(currentList);
								currentList = &queue43;
							}
						}
					}
					if(isEmpty(&queue5) == false)
					{
						if(ticksThisRun != 0)
						{
							//if a run has finished and ticksThisRun is not 0 then we haven't deleted it yet and need to decrease priority before rotation
							if(runFinished == true && (currentList->head->data->numOfTimesServiced==5 && (currentList==&queue6||currentList==&queue5)) || (currentList->head->data->numOfTimesServiced==2 && (currentList==&queue43)))
							{
								currentList->head->data->priority--;
								if(currentList->head->data->priority == 2)
								{
									currentList->head->data->age = 0;
									process* data = removeNode(currentList, currentList->head);
									node temp=initNode(data);
									add(&queue21, &temp);
								}
								else
								{
									rotate(currentList);
								}
							}
							else
							{
								rotate(currentList);
							}
						}
						currentList = &queue5;
						ticksThisRun = 0;
					}
				}
				if(isEmpty(&queue6) == false)
				{
					if(ticksThisRun != 0)
					{
						 //if a run has finished and ticksThisRun is not 0 then we haven't deleted it yet and need to decrease priority before rotation
						if(runFinished == true && (currentList->head->data->numOfTimesServiced==5 && (currentList==&queue6||currentList==&queue5)) || (currentList->head->data->numOfTimesServiced==2 && (currentList==&queue43)))
						{
							currentList->head->data->priority--;
							if(currentList->head->data->priority == 2)
							{
								currentList->head->data->age = 0;
								process* data = removeNode(currentList, currentList->head);
								node temp=initNode(data);
								add(&queue21, &temp);
							}
							else if(currentList->head->data->priority == 4)
							{
								currentList->head->data->age = 0;
								process* data = removeNode(currentList, currentList->head);
								node temp=initNode(data);
								add(&queue43, &temp);
							}
							else
							{
								rotate(currentList);
							}
						}
						else
						{
							rotate(currentList);
						}
					}
							printf("ARE U THE CULPRIT?2 /n");
					currentList = &queue6;
					ticksThisRun = 0;
				}
			}
		}
		//if a run has finished and ticksThisRun is not 0 then we haven't deleted it yet and need to decrease priority before rotation
		//Decrease priority if needed, and rotate if needed
		if(ticksThisRun != 0 && runFinished == true)
		{
			int numOfTimesServiced=currentList->head->data->numOfTimesServiced;
			if((numOfTimesServiced==5 && (currentList==&queue6||currentList==&queue5)) || (numOfTimesServiced==2 && (currentList==&queue43))){
				int temp=currentList->head->data->priority--;
				currentList->head->data->numOfTimesServiced = 0;
				currentList->head->data->age = 0;
				if(currentList==&queue6 && temp<6){
					process* data = removeNode(currentList, currentList->head);
					node temp=initNode(data);
					add(&queue5, &temp);
				}else if(currentList==&queue5){
					process* data = removeNode(currentList, currentList->head);
					node temp=initNode(data);
					add(&queue5, &temp);
				}else if(currentList==&queue43){
					process* data = removeNode(currentList, currentList->head);
					node temp=initNode(data);
					add(&queue5, &temp);
				}else{
					printf("current list is inproperly set, check //decrease priority if needed");
				}
			}
			rotate(currentList);
			ticksThisRun = 0;
		}
		//increment the current process.
		
		//check if the current process needs to be moved to the back of the line or demoted to another queue.
		//queue 1 runs are 5  ticks and priority is reduced
		//queue 2 runs are 10 ticks long and needs their priority reduced by one every 2 runs or 20 cycles.
		//queue 3 runs are 20 ticks
		//ageing section starts here

		int a=0;
		if(currentList==&queue6){
			a=6;
		}
		else if(currentList==&queue5){
			a=5;
		}
		else if(currentList==&queue43){
			a=43;
		}else{
			a=21;
		}
		printf("current list is %d\n", a);
		if(currentList==NULL)printf("head was Null\n");
		printf("skeletons = %d \n", skeletons);
		printf("Current node is %s \n", currentList->head->data->ID );  ////////////////////////CAUSING THE FAULT
		//between 256 and 427 currentList->head->data->ID goes from the s3 it should be to some kind of segfaulting null
		printf("Current node still needs  %d \n", currentList->head->data->cpu);
		if(runFinished){
			//age everything by 1
			node* walker=queue21.head;
			if(walker != NULL)
			{
				do{
					printf("doing\n");
					walker->data->age++;
					//also needs to check if age has gone over;
					if(walker->data->age>7){
						walker->data->priority++;
						walker->data->age = 0;
						if(walker->data->priority>2){
							process* temp;
							if(queue21.head->next == NULL)
							{
								temp = queue21.head->data;
								queue21 = initList();
							}
							else
							{
								temp = removeNode(&queue21, walker);
							}
							node newNode=initNode(temp);
							newNode.data->numOfTimesServiced=0;
							add(&queue43, &newNode);
						}
					}
					walker=walker->next;
					printf("inside while do 1\n");
				}while(walker!=queue21.head && walker != NULL);
			}
			walker=queue43.head;
			if(walker != NULL)
			{
				do{
					printf("%s \n",walker->data->ID);
					printf("%d \n",walker->data->age);
					walker->data->age++;
					//also needs to check if age has gone over;
					if(walker->data->age>7){
						walker->data->priority++;
						walker->data->age = 0;
						if(walker->data->priority>4){
							process* temp;
							if(queue43.head->next == NULL)
							{
								temp = queue43.head->data;
								queue43 = initList();
							}
							else
							{
								temp = removeNode(&queue43, walker);
							}
							node newNode=initNode(temp);
							add(&queue5, &newNode);
						}
					}
					walker=walker->next;
					printf("inside while do 2\n");
				}while(walker!=queue43.head && walker != NULL);
			}
			//might have some problems here so printing a reminder
			runFinished=false;
		}
		//if current process is being run for the first time set its ready time
		if(currentList != NULL)
		{
			if(currentList->head->data->readyTime == -1)
			{
				currentList->head->data->readyTime = tick;
			}
			ticksThisRun++;
			currentList->head->data->cpu--;
			currentList->head->data->age = 0;
		}
		//promote processes
		tick++;

	}
	node * printNode = &graveyard[0];
	for(int a = 0; a < skeletons; a++)
	{
		int wait = printNode->data->endTime - printNode->data->readyTime - printNode->data->cpuOriginal;
		printf("%s     %d     %d     %d     %d     %d     %d",printNode->data->ID,printNode->data->priority,printNode->data->init,printNode->data->endTime,printNode->data->readyTime,printNode->data->cpuOriginal,wait);
		printNode = &graveyard[a];
	}
    return 0;
}