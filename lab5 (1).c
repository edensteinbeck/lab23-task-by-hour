//      winter 2023
//		task list with hour

//  includes
#include     <stdio.h>
#include	<string.h>
union infos{
    float budget;
    char location[100];
    int endtime[2];
};

struct info
{
    char tasks[100];
    int hours;
    int minutes;
    union infos infounion;
};
int counter=0;

struct info tasklist[10];
 
// functions
 
int  main(void);
void insert(void);
void list(void);
void listhour(void);
void delete(void);
void deleteHour(void);
int check_duplicate(char tempTask[]);


// main
int
main (void)
{
    while (1)
    {
       printf("Enter option\n");	// requests input to run each option
       int option;
       if (scanf("%d",&option)!=1)	// checks that valid number was inputted
       {
	 printf("Error\n");
	 return 0;
       }
       switch (option)
       {
	 case 1:			// run input
	   insert();
	   break;
	 case 2:			// run list
	   printf("Your tasks are:\n");
	   list();
	   break;
	 case 3:			// run listhour
	    listhour();
	    break;
	 case 4:
	    delete();
	    break;
	 case 5:
	    deleteHour();
	    break;
 	 case 0:			// quit
	    printf("Exit\n");
	    return 0;
	 default:
	    printf("Wrong option\n");
       }
    }
 }


// insert a task (string) to do at a time
// can only insert if there are less than 10 tasks in the list
// will keep in order by hour
void
insert()    
{
    
    if (counter<10)	    // checks that list is not full
    {

      printf("Task:\n");
      __fpurge(stdin);
      char tempTask[100];
      char checkedTemp[100];
      scanf("%s",tempTask);

      if (check_duplicate(tempTask) == 0)
      {
	  printf("Duplicate task\n");
      }

      else
      {
	strcpy(checkedTemp,tempTask);

	// ask for input, checks that input is within correct range
	printf("At what hour?\n");
	__fpurge(stdin);

	int tempTime;
	scanf("%d", &tempTime);
	if (tempTime <= 24) 
	{
	   // tasklist.hours[counter] = tempTime;

	    printf("At what minute? (00-59)\n");
	    __fpurge(stdin);
	    int tempMinute;
	    scanf("%d", &tempMinute);

	    if (tempMinute <= 59)
	    {
	    }
	    else
	    {
		printf("Must be a minute between 00-59\nTry again\n");
		counter--;
	    }   
     

	    // find correct time  index to input task
	    int i,j;
	    int index = counter;
	    if ( counter != 0)
	    {
		for (i = 0; i < counter; i++)
		{
		    if (tempTime < tasklist[i].hours)
		    {
			index = i;
			break;
		    }
		    if (tempTime == tasklist[i].hours && tempMinute <= tasklist[i].minutes)
		    {
			index = i;
			break;
		    }

		    }
	    }
	    
	    else 
	    {
		index = 0;
	    }

	    // make a space
	    for (j = counter; j>index;j--)
	    {
		tasklist[j]=tasklist[j-1];
	        strcpy(tasklist[j].tasks,tasklist[j-1].tasks);
		tasklist[j].hours = tasklist[j-1].hours;
		tasklist[j].minutes = tasklist[j-1].minutes;
	    }   
	
	    // add the task to that spot in the list
	    strcpy(tasklist[index].tasks,checkedTemp);
	    tasklist[index].hours = tempTime;
	    tasklist[index].minutes = tempMinute;

    
	     // ask for budget, location, endtime
  
	     if (tempTime < 12)
	     {
		 printf("What is your budget for this task?\n");
                 scanf("%f", &tasklist[index].infounion.budget);
             }
  
             if (tempTime >= 12 && tempTime <= 20)
             {
                  char tempString[50];
                  printf("What is the location of this task?\n");
		  __fpurge(stdin);
                  scanf("%s", tempString);
  
		  int i=0;
		  while(tempString[i] != '\0')
		  { 
		  tasklist[index].infounion.location[i] = tempString[i];
		  i++;
		  }

	     }

	     if (tempTime > 20)
	     {
	         int tempHour, tempMin;
	         printf("What hour would you like to finish this task?\n");
	         scanf("%i",&tempHour);
	         if (tempHour < 24)
	         {
		      tasklist[index].infounion.endtime[0] = tempHour;
	         }   
	         else
	         {
		      printf("Invalid hour\n");
		      return;
	    	 }   
			     
		 printf("What minute would you like to finish this task?\n");
		 __fpurge(stdin);
		 scanf("%i", &tempMin);

		 if (tempMin < 60)
		 {
		    tasklist[index].infounion.endtime[1] = tempMin;
		 }
		 else
		 {
		    printf("Invalid minute\n");
		 }
             }
    }

    else 
    {
        printf ("Must be a time between 1-24. Try Again\n");
        counter--;
    }
	
    counter++;

    }    
  }

  else
  {
    printf("List is full, must delete an item\n");
  }

}

// list

void list()
{

    struct info *p; 
    p = tasklist;
    if (counter > 0)	    // checks that there are items in lists
    {
      int i;
      for (i =0; i<counter; i++,p++)    // prints values
      {
	 printf("Task %d:\n", counter); 
	 printf("%s\n", p->tasks);
	 printf("at %d:%02d\n", p->hours,p->minutes);

	 // prints values stored in the union
	 if (p->hours < 12)
	 {
	    printf("Budget: %.2f\n",p->infounion.budget);
	 }

	 if (p->hours >= 12 && p->hours <= 20)
	 {
	    printf("Location: %s\n", p->infounion.location);
	 }

	 if (p->hours > 20)
	 {
	    printf("End time: %i:%02i\n", p->infounion.endtime[0], p->infounion.endtime[1]); 
	 }
	 printf("\n");
      }

    }

    else
    {
      printf("No tasks\n");
    }
}


// list

void listhour()	  
{
    struct info *p;
    p = tasklist;
    if (counter>0)  // checks that there are tasks in the array 
    {

      int requestedtime;
      printf("Tasks at which time?\n");
      scanf("%d",&requestedtime);

      int i;
      int j=0;				// flag (used lines 127-130)
      for (i = 0; i < counter; i++,p++)	// loops through time[] to find applicable time
      {					// and displays corresponding task
       	if (requestedtime == p->hours)
	    {
	    printf("%s at %d:%02d,", p->tasks,p->hours,p->minutes);
	    j++;			    

	    if (requestedtime < 12)
	    {
		printf( " budget is %.2f\n",p->infounion.budget);
	    }

	    if (requestedtime >= 12 && requestedtime <= 20)
	    {
		printf(" location is %s\n", p->infounion.location);
	    }

	    if (requestedtime > 20)
	    {
		printf(" end time is %d:%02\n", p->infounion.endtime[0], p->infounion.endtime[1]);
	    }
	}	
	} 

      if (j==0)		// indicates that the time inputted is not in time[]
      {   
	printf("No tasks at this time\n");
      }

     }

   else
   {
     printf("No tasks in this list\n");
   }
}


// delete

void delete()
{
    
    char delTask[100];
    printf("What task would you like to delete?\n");
    __fpurge(stdin);
    scanf("%s",delTask);

    // check if task is in the list
    if (check_duplicate(delTask) == 0)
    {
	int taskIndex =0;
	int i;
	char blank[3] = " ";
	for (i = 0; i < counter; i++)
	{
	    // find where the task is in the list
	    if (strcmp(tasklist[i].tasks, delTask) == 0)
	    {
		taskIndex = i;
	    }
	}

	//remove from list
	while (taskIndex <  counter-1)
	{
	   strcpy(tasklist[taskIndex].tasks,tasklist[taskIndex+1].tasks);
	   tasklist[taskIndex].hours = tasklist[taskIndex+1].hours;
	   tasklist[taskIndex].minutes = tasklist[taskIndex+1].minutes;
	    taskIndex++;
	}

	if (taskIndex == counter-1) // remove the last item in list
	{
	    strcpy(tasklist[counter].tasks,blank);
	    tasklist[counter].hours = 0;
	    tasklist[counter].minutes = 0;
	    counter--;
	}
    

    }
    
    else
    {
	printf("Task does not exist\n");
    }

}


// check for duplicate tasks

int 
check_duplicate(char tempTask[])
{

    int i;
    for (i = 0; i < counter; i++)
    {
	if (strcmp(tasklist[i].tasks,tempTask) == 0)
	{
	return 0;
	}
	
    }
    return 1;



}

void deleteHour()
{
  int tempHour = 0;
   int tempIndex = 0;
  // struct info *p;
  // p=tasklist;

    printf("At what hour would you like to delete tasks?\n");
    __fpurge(stdin);
    scanf("%i", &tempHour);

    int i,j;
    for (i=0; i<counter; i++)
    {
	if (tempHour == tasklist[i].hours)
	{
	    printf("%d", tempHour);
	    for(j = i; j < counter-1; j++)
	    {
	   strcpy(tasklist[j].tasks,tasklist[j+1].tasks);
	   tasklist[j].hours = tasklist[j+1].hours;
	   tasklist[j].minutes = tasklist[j+1].minutes;
	    }
	   counter--;
	printf("%i", counter);
	   i = 0;
	}
    }			


}
