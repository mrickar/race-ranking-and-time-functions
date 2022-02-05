#include <stdlib.h>
#include <stdio.h>

#define n_sector 3


float ***create_sector_times(unsigned int *n_drivers, unsigned int *n_laps)
{
    int i, j, k;
    float ***sector_times;
    scanf("%u %u", n_drivers, n_laps);
    sector_times = malloc(sizeof(float **) * (*n_drivers));
    for (i = 0; i < *n_drivers; i++)
    {
        sector_times[i] = malloc(sizeof(float *) * (*n_laps));
        for (j = 0; j < *n_laps; j++)
        {
            sector_times[i][j] = malloc(sizeof(float) * n_sector);
        }
    }
    for (i = 0; i < *n_drivers; i++)
    {
        for (j = 0; j < *n_laps; j++)
        {
            for (k = 0; k < n_sector; k++)
            {
                scanf("%f", &sector_times[i][j][k]);
            }
        }
    }
    return sector_times;
}

unsigned int **create_positions(unsigned int *p_drivers, unsigned int *n_races)
{
    int i, j;
    unsigned int **positions;
    scanf("%u %u", p_drivers, n_races);
    positions = malloc(sizeof(unsigned int *) * (*p_drivers));
    for (i = 0; i < *p_drivers; i++)
    {
        positions[i] = malloc(sizeof(unsigned int) * (*n_races));
    }
    for (i = 0; i < (*p_drivers); i++)
    {
        for (j = 0; j < (*n_races); j++)
        {
            scanf("%u", &positions[i][j]);
        }
    }
    return positions;
}

float **calculate_lap_times(float ***sector_times, unsigned int n_drivers, unsigned int n_laps)
{
    int i, j, k;
    float **calculated_lap_times;
    calculated_lap_times = malloc(sizeof(float *) * n_drivers);
    for (i = 0; i < n_drivers; i++)
    {
        calculated_lap_times[i] = malloc(sizeof(float) * n_laps);
    }
    for (i = 0; i < n_drivers; i++)
    {
        for (j = 0; j < n_laps; j++)
        {
            float tmp = 0;
            for (k = 0; k < n_sector; k++)
            {
                tmp += sector_times[i][j][k];
            }
            calculated_lap_times[i][j] = tmp;
        }
    }
    return calculated_lap_times;
}

unsigned int find_fastest_lap(float **lap_times, unsigned int n_drivers, unsigned int n_laps)
{
    int i, j;
    unsigned int ans;
    float min;
    for (i = 0; i < n_drivers; i++)
    {
        for (j = 0; j < n_laps; j++)
        {
            if (i == 0 && j == 0)
            {
                min = lap_times[i][j];
                ans = 0;
            }
            if (lap_times[i][j]+0.0001 < min)
            {
                min = lap_times[i][j];
                ans = i;
            }
        }
    }
    return ans;
}

unsigned int find_driver_fastest_lap(float **sector_times_of_driver, unsigned int n_laps)
{
    int i, j;
    float min;
    unsigned int ans;
    for (i = 0; i < n_laps; i++)
    {
        float tmp = 0;
        for (j = 0; j < n_sector; j++)
        {
            tmp += sector_times_of_driver[i][j]; /*calculating the i'th lap time by adding sector times*/
        }
        if (i == 0)
        {
            min = tmp;
            ans = 0;
        }
        if (tmp+0.0001 < min)
        {
            min = tmp;
            ans = i;
        }
    }
    return ans;
}

float *selection_sort(float *arr, unsigned int len, char ord)
{
    int i, j;
    float *new_arr = malloc(sizeof(float) * len);
    for (i = 0; i < len; i++)
    {
        new_arr[i] = arr[i];
    }
    if (ord == 'A')
    {
        for (i = 0; i < len; i++)
        {
            float mn, tmp;
            int ind;
            ind = i;
            mn = new_arr[i];
            for (j = i + 1; j < len; j++)
            {
                if (new_arr[j] < mn)
                {
                    mn = new_arr[j];
                    ind = j;
                }
            }
            tmp = new_arr[i];
            new_arr[i] = mn;
            new_arr[ind] = tmp;
        }
    }
    else if (ord == 'D')
    {
        for (i = 0; i < len; i++)
        {
            float mx, tmp;
            int ind;
            ind = i;
            mx = new_arr[i];
            for (j = i + 1; j < len; j++)
            {
                if (new_arr[j] > mx)
                {
                    mx = new_arr[j];
                    ind = j;
                }
            }
            tmp = new_arr[i];
            new_arr[i] = mx;
            new_arr[ind] = tmp;
        }
    }
    return new_arr;
}

unsigned int *find_finishing_positions(float **lap_times, unsigned int n_drivers, unsigned int n_laps)
{
    int i, j;
    unsigned int *finishing_positions = malloc(sizeof(unsigned int) * n_drivers);
    float *total_lap_times = malloc(sizeof(float) * n_drivers);
    for (i = 0; i < n_drivers; i++)
    {
        float tmp = 0;
        for (j = 0; j < n_laps; j++)
        {
            tmp += lap_times[i][j];
        }
        total_lap_times[i] = tmp;
    }
    for (i = 0; i < n_drivers; i++)
    {
        float mn = -1;
        int ind;
        for (j = 0; j < n_drivers; j++)
        {
            if (mn == -1 && total_lap_times[j] != -1)
            {
                mn = total_lap_times[j];
                ind = j;
            }
            else if (total_lap_times[j]+0.0001 < mn && total_lap_times[j] != -1)
            {
                mn = total_lap_times[j];
                ind = j;
            }
        }
        finishing_positions[i] = ind;
        total_lap_times[ind] = -1;
    }
    return finishing_positions;
}

float *find_time_diff(float **lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
                      unsigned int driver2)
{
    int i;
    float *time_diff = malloc(sizeof(float) * n_laps);
    for (i = 0; i < n_laps; i++)
    {
        if (i == 0)
        {
            time_diff[i] = lap_times[driver1][i] - lap_times[driver2][i];
            continue;
        }
        time_diff[i] = time_diff[i - 1] + lap_times[driver1][i] - lap_times[driver2][i];
    }
    return time_diff;
}

unsigned int *calculate_total_points(unsigned int **positions, unsigned int p_drivers, unsigned int n_races)
{
    int i, j;
    unsigned int *position_point = malloc(sizeof(unsigned int) * p_drivers);
    unsigned int *total_points = malloc(sizeof(unsigned int) * p_drivers);

    for (i = 0; i < p_drivers; i++)
    {
        scanf("%u", &position_point[i]);
    }
    for (i = 0; i < p_drivers; i++)
    {
        unsigned int tmp = 0;
        for (j = 0; j < n_races; j++)
        {
            tmp += position_point[positions[i][j] - 1];
        }
        total_points[i] = tmp;
    }
    return total_points;
}

unsigned int find_season_ranking(unsigned int *total_points, unsigned int p_drivers, unsigned int id)
{
    int i;
    unsigned int point_of_driver = total_points[id], season_ranking = 1;

    for (i = 0; i < p_drivers; i++)
    {
        if (total_points[i] > point_of_driver || (total_points[i] == point_of_driver && i < id))
        {
            season_ranking++;
        }
    }
    return season_ranking;
}
