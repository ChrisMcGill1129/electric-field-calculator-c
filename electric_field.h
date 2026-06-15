#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H
#include <math.h>
#define PICO (1e-12)
#define NANO (1e-9)
#define MICRO (1e-6)
#define MILLI (1e-3)
#define NORMAL (1e+0)
#define KILO (1e+3)
#define MEGA (1e+6)
#define K (9e+9)
#define CENTI (1e+2)

typedef struct{
    //double for electric field, source and test charges, and distance
    double ef;
    double qsource;
    double qtest;
    double distance;
    //-----include an array of char's to store the size of each-----
    char *qsource_size;
    char *qtest_size;
    char *distance_size;
    //-----include the real values of each (like if nano, then use qsource*nano)
    //we don't need one for the electric field because that will just be in N/C
    double qsource_real;
    double qtest_real;
    double distance_real;
} Electric_field;

//a struct to store an array of Electric_field structs, and the size/capacity
//in order to reallocate memory later on if needed
typedef struct{
    Electric_field *fields;
    int size;
    int capacity;
} Fields_log;


//------------PROTOTYPES--------------


//pass in (fields, user input, something like
//('nano')) in order to get the real qsource size in order to avoid
//making one function too long (like last time). This will work by
//taking in field, finding field->qsource_size, and if qsource_size
//is nano, micro, pico etc, it'll make it like EX: qsource_real = qsource*NANO;
//itll also ask the user (using a while loop) for the size of the source charge
//to make this happen, like 'what is the size of qsource' and if the user
//enters 'nano', it'll make qsource_size = 'nano', and then use that to
//get the real size
void source_charge_size(Electric_field *field);
//do the same as above
void test_charge_size(Electric_field *field);
//same as above
void distance_size(Electric_field *field);
//use the above three functions and this one below to get 2 of the 4 values
void get_values(Fields_log *log);
//get the test charge because it's always going to be needed, unless
//we use force analysis, which I wont be doing here
void get_test_charge(Electric_field *field);
//if the user choses to enter values for source charge and distance, calcualte
//the electric fields value
void calculate_electric_field(Electric_field *field);
//same as above, just for distance this time
void calculate_distance(Electric_field *field);
//same as above, jsut for the source charge
void calculate_source_charge(Electric_field *field);
//use a for loop to loop through the log->fields[i] etc to print out all values
void print_values(const Fields_log *log);
//use another for loop to free all dynamically allocated memory
void free_memory(Fields_log *log);
void reallocate_memory(Fields_log *log);
void get_electric_field(Electric_field *field);
void get_source_charge(Electric_field *field);
void get_distance(Electric_field *field);


#endif





