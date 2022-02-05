#include "functions.h"

/*
You will not submit this file, just use for testing your code.
All your implementations should be in functions.c
*/

void print_3d(float ***sector_times, unsigned int n_drivers, unsigned int n_laps)
{
    int i, j, k;
    for (i = 0; i < n_drivers; i++)
    {
        printf("%d. driver:\n", i);
        for (j = 0; j < n_laps; j++)
        {
            printf("\t%d. lap: ", j);
            for (k = 0; k < 3; k++)
            {
                printf("%f ", sector_times[i][j][k]);
            }
            printf("\n");
        }
    }
}
void print_2d(unsigned int **arr, unsigned int row, unsigned int col)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        printf("%d.row:", i);
        for (j = 0; j < col; j++)
        {
            printf("%u ", arr[i][j]);
        }
        printf("\n");
    }
}
void print_1d(unsigned int *arr, unsigned int row)
{
    int i = 0;
    for (i = 0; i < row; i++)
    {
        printf("%u ", arr[i]);
    }
}
int main()
{
    unsigned int fastest_lap, **positions;
    unsigned int *drivers_fastest_lap,*finishing_pos, *total_points;
    float ***sector_times, **lap_times;
    int i, j, k;
    unsigned int n_drivers, n_laps, p_drivers, n_races;
    float arr[]={5.32,4.31,6.43,1.9,2.53,5.44,9.14,6.43};
    float *ordered;
    /*sector_times = create_sector_times(&n_drivers, &n_laps);*/
    /*drivers_fastest_lap = malloc(sizeof(unsigned int) * n_drivers);
    print_3d(sector_times, n_drivers, n_laps);*/
    positions=create_positions(&p_drivers,&n_races);
    print_2d(positions,p_drivers,n_races);
    /*lap_times = calculate_lap_times(sector_times,n_drivers,n_laps);
    print_2d(lap_times,n_drivers,n_laps);*/
    /*fastest_lap = find_fastest_lap(lap_times,n_drivers,n_laps);*/
    /*for(i=0;i<n_drivers;i++)
    {
        drivers_fastest_lap[i]=find_driver_fastest_lap(sector_times[i],n_laps);
    }*/
    /*print_1d(drivers_fastest_lap,n_drivers);*/

    /*ordered=selection_sort(arr,8,'A');
    print_1d(ordered,8);*/
    /*float *time_dif;
    lap_times=malloc(sizeof(float*)*2);
    lap_times[0]=malloc(sizeof(float)*3);
    lap_times[1]=malloc(sizeof(float)*3);
    lap_times[0][0]=18;
    lap_times[0][1]=21;
    lap_times[0][2]=20;
    lap_times[1][0]=20;
    lap_times[1][1]=20;
    lap_times[1][2]=22;
    time_dif=find_time_diff(lap_times,2,3,0,1);
    print_1d(time_dif,3);*/
    total_points=calculate_total_points(positions,10,n_races);
    print_1d(total_points,p_drivers);
    return 0;
}
