#include "electric_field.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void reallocate_memory(Fields_log *log){
    log->capacity *= 2;

    Electric_field *temp = realloc(log->fields, sizeof(Electric_field) *
            log->capacity);
    if(temp == NULL){
        printf("Failed to reallocate memory\n");
        exit(1);
    }

    log->fields = temp;

}

//in main, pass in log to get its values for its fields array
void get_values(Fields_log *log){
    int count = 0;
    while(1){
        char choice[100];
        printf("Do you wish to continue (y/n): ");
        fgets(choice, sizeof(choice), stdin);
        //replace newline character with null terminator
        choice[strcspn(choice, "\n")] = '\0';
        //if the user wishes to continue, get values
        if(strcmp(choice, "y") == 0){
            if(log->size >= log->capacity){
                reallocate_memory(log);
            }
            get_test_charge(&log->fields[count]);
            printf("What is the first variable: \n");
            printf("Electric Field (e), Source Charge (s), Distance (d): ");
            char first_choice[100];
            char second_choice[100];
            fgets(first_choice, sizeof(first_choice), stdin);
            first_choice[strcspn(first_choice, "\n")] = '\0';
            if(strcmp(first_choice, "e") == 0){
                //if the users first input is the ef, pass that
                //into t`he get_electric_field function
                get_electric_field(&log->fields[count]);
                while(1){
                    printf("What is your second choice: Source (s) Distance (d): ");
                    fgets(second_choice, sizeof(second_choice), stdin);
                    second_choice[strcspn(second_choice, "\n")] = '\0';

                    if(strcmp(second_choice, "s") == 0){
                        get_source_charge(&log->fields[count]);
                        calculate_distance(&log->fields[count]);
                        break;
                    }

                    else if(strcmp(second_choice, "d") == 0){
                        get_distance(&log->fields[count]);
                        calculate_source_charge(&log->fields[count]);
                        break;
                    }

                    else{
                        printf("Invalid second choice, try again\n");
                        continue;
                    }
                }
            }
            else if(strcmp(first_choice, "d") == 0){
                get_distance(&log->fields[count]);
                printf("What is your second choice: Source charge (s), ef (e): ");
                while(1){
                    fgets(second_choice, sizeof(second_choice), stdin);
                    second_choice[strcspn(second_choice, "\n")] = '\0';
                    if(strcmp(second_choice, "s") == 0){
                        get_source_charge(&log->fields[count]);
                        calculate_electric_field(&log->fields[count]);
                        break;
                    }
                    else if(strcmp(second_choice, "e") == 0){
                        get_electric_field(&log->fields[count]);
                        calculate_source_charge(&log->fields[count]);
                        break;
                    }
                    else{
                        printf("Invalid second choice, try again\n");
                        continue;
                    }
                }
            }
            else if(strcmp(first_choice, "s") == 0){
                get_source_charge(&log->fields[count]);
                while(1){
                    printf("What is the second choice (ef (e), distance (d)): ");
                    fgets(second_choice, sizeof(second_choice), stdin);
                    second_choice[strcspn(second_choice, "\n")] = '\0';

                    if(strcmp(second_choice, "d") == 0){
                        get_distance(&log->fields[count]);
                        calculate_electric_field(&log->fields[count]);
                        break;
                    }

                    else if(strcmp(second_choice, "e") == 0){
                        get_electric_field(&log->fields[count]);
                        calculate_distance(&log->fields[count]);
                        break;
                    }

                    else{
                        printf("Invalid second choice, try again\n");
                        continue;
                    }
                }
            }
            else{
                printf("Invalid first choice, only enter 'e', 's', or 'd'\n");
                continue;
            }
            count++;
            log->size++;
        }
        else if(strcmp(choice, "n") == 0){
            break;
        }
        else{
            printf("ERROR: Invalid Input, Only Enter 'y' Or 'n'\n");
            continue;
        }
    }
}

void get_electric_field(Electric_field *field){
    printf("What is the value for the electric field in N/C: ");
    scanf("%lf", &field->ef);
    while(getchar() != '\n'){
    }
}

void get_source_charge(Electric_field *field){
    printf("What is the value for the source charge: ");
    scanf("%lf", &field->qsource);
    while(getchar() != '\n'){
    }
    source_charge_size(field);
}

void source_charge_size(Electric_field *field){
    char size[100];
    printf("What is the size of the source charge (nano, micro, pico, etc): ");
    fgets(size, sizeof(size), stdin);
    size[strcspn(size, "\n")] = '\0';
    if(strcmp(size, "nano") == 0){
        field->qsource_size = malloc(strlen("nano") + 1);
        strcpy(field->qsource_size, "nano");
        field->qsource_real = field->qsource * NANO;
    }
    else if(strcmp(size, "micro") == 0){
        field->qsource_size = malloc(strlen("micro") + 1);
        strcpy(field->qsource_size, "micro");
        field->qsource_real = field->qsource * MICRO;
    }
    else if(strcmp(size, "pico") == 0){
        field->qsource_size = malloc(strlen("pico") + 1);
        strcpy(field->qsource_size, "pico");
        field->qsource_real = field->qsource * PICO;
    }
    else{
        printf("Invalid input, set to default of Coulomb\n");
        field->qsource_size = malloc(strlen("") + 1);
        strcpy(field->qsource_size, "");
        field->qsource_real = field->qsource * NORMAL;
    }
}

void get_distance(Electric_field *field){
    printf("What is the value for the distance: ");
    scanf("%lf", &field->distance);
    while(getchar() != '\n'){
    }
    distance_size(field);
}

void distance_size(Electric_field *field){
    printf("What is the size of the distance (kilo, mega, milli, centi, etc: ");
    char size[100];
    fgets(size, sizeof(size), stdin);
    size[strcspn(size, "\n")] = '\0';
    if(strcmp(size, "nano") == 0){
        field->distance_size = malloc(strlen("nano") + 1);
        strcpy(field->distance_size, "nano");
        field->distance_real = field->distance * NANO;
    }
    else if(strcmp(size, "micro") == 0){
        field->distance_size = malloc(strlen("micro") + 1);
        strcpy(field->distance_size, "micro");
        field->distance_real = field->distance * MICRO;
    }
    else if(strcmp(size, "pico") == 0){
        field->distance_size = malloc(strlen("pico") + 1);
        strcpy(field->distance_size, "pico");
        field->distance_real = field->distance * PICO;
    }
    else if(strcmp(size, "kilo") == 0){
        field->distance_size = malloc(strlen("kilo") + 1);
        strcpy(field->distance_size, "kilo");
        field->distance_real = field->distance * KILO;
    }
    else if(strcmp(size, "mega") == 0){
        field->distance_size = malloc(strlen("mega") + 1);
        strcpy(field->distance_size, "mega");
        field->distance_real = field->distance * MEGA;
    }
    else if(strcmp(size, "centi") == 0){
        field->distance_size = malloc(strlen("centi") + 1);
        strcpy(field->distance_size, "centi");
        field->distance_real = field->distance * CENTI;
    }
    else if(strcmp(size, "milli") == 0){
        field->distance_size = malloc(strlen("milli") + 1);
        strcpy(field->distance_size, "milli");
        field->distance_real = field->distance * MILLI;
    }
    else{
        printf("Invalid input, set to default of meter\n");
        field->distance_size = malloc(strlen("") + 1);
        strcpy(field->distance_size, "");
        field->distance_real = field->distance * NORMAL;
    }
}

void get_test_charge(Electric_field *field){
    char size[100];
    printf("What is the test charge: ");
    scanf("%lf", &field->qtest);
    while(getchar() != '\n'){
    }
    printf("What is the size of the test charge (nano, micro, pico): ");
    fgets(size, sizeof(size), stdin);
    size[strcspn(size, "\n")] = '\0';

    if(strcmp(size, "nano") == 0){
        field->qtest_size = malloc(strlen("nano") + 1);
        strcpy(field->qtest_size, "nano");
        field->qtest_real = field->qtest * NANO;
    }
    else if(strcmp(size, "micro") == 0){
        field->qtest_size = malloc(strlen("micro") + 1);
        strcpy(field->qtest_size, "micro");
        field->qtest_real = field->qtest * MICRO;
    }
    else if(strcmp(size, "pico") == 0){
        field->qtest_size = malloc(strlen("pico") + 1);
        strcpy(field->qtest_size, "pico");
        field->qtest_real = field->qtest * PICO;
    }
    else{
        printf("Invalid input, set to default of Coulomb\n");
        field->qtest_size = malloc(strlen("") + 1);
        strcpy(field->qtest_size, "");
        field->qtest_real = field->qtest * NORMAL;
    }
}

void calculate_electric_field(Electric_field *field){
    //use the formula E(r) = k(qsource)/r^2
    double x = field->distance_real;
    double y = x * x;
    field->ef = (K * field->qsource_real) / y;
}

void calculate_source_charge(Electric_field *field){
    //use formula qsource = E(r)*r^2 / k;
    double z = field->distance_real;
    double s = z * z;
    field->qsource_real = (field->ef * s)/K;
    if(field->qsource_real >= MILLI){
        field->qsource = field->qsource_real / MILLI;
        field->qsource_size = malloc(strlen("milli") + 1);
        strcpy(field->qsource_size, "milli");
    }
    else if(field->qsource_real >= MICRO){
        field->qsource = field->qsource_real / MICRO;
        field->qsource_size = malloc(strlen("micro") + 1);
        strcpy(field->qsource_size, "micro");
    }
    else if(field->qsource_real >= NANO){
        field->qsource = field->qsource_real / NANO;
        field->qsource_size = malloc(strlen("nano") + 1);
        strcpy(field->qsource_size, "nano");
    }
    else{
        field->qsource = field->qsource_real / PICO;
        field->qsource_size = malloc(strlen("pico") + 1);
        strcpy(field->qsource_size, "pico");
    }
}

void calculate_distance(Electric_field *field){
    double distance_squared = ((K * field->qsource) / field->ef);
    field->distance = sqrt(distance_squared);
    double real_distance_unsquared = ((K * field->qsource_real) / field->ef);
    field->distance_real = sqrt(real_distance_unsquared);

    if(field->distance_real >= NANO && field->distance_real < PICO){
    field->distance_size = malloc(strlen("nano") + 1);
    strcpy(field->distance_size, "nano");
    }

    else if(field->distance_real > NANO){
        field->distance_size = malloc(strlen("pico") + 1);
        strcpy(field->distance_size, "pico");
    }

    else if(field->distance_real >= MICRO && field->distance_real < NANO){
        field->distance_size = malloc(strlen("micro") + 1);
        strcpy(field->distance_size, "micro");
    }

    else if(field->distance_real >= MILLI && field->distance_real < MICRO){
        field->distance_size = malloc(strlen("milli") + 1);
        strcpy(field->distance_size, "milli");
    }
    else if(field->distance_real >= KILO && field->distance_real < MEGA){
            field->distance_size = malloc(strlen("kilo") + 1);
            strcpy(field->distance_size, "kilo");
    }
    else if(field->distance_real > KILO){
            field->distance_size = malloc(strlen("mega") + 1);
            strcpy(field->distance_size, "mega");
    }
    else{
        field->distance_size = malloc(strlen("") + 1);
        strcpy(field->distance_size, "");
    }
}

void print_values(const Fields_log *log){
    for(int i = 0; i < log->size; i++){
        printf("---------------ENTRY %d----------------\n", i + 1);
        printf("Electric Field: %e N/C\n", log->fields[i].ef);
        printf("Source Charge: %e %scoulombs\n", log->fields[i].qsource, 
                log->fields[i].qsource_size);
        printf("Test Charge: %e %scoulombs\n", log->fields[i].qtest,
                log->fields[i].qtest_size);
        printf("Distance: %e %smeters\n", log->fields[i].distance,
                log->fields[i].distance_size);
    }
}

void free_memory(Fields_log *log){
    for(int i = 0; i < log->size; i++){
        free(log->fields[i].qsource_size);
        free(log->fields[i].qtest_size);
        free(log->fields[i].distance_size);
    }
    free(log->fields);
    free(log);
}

