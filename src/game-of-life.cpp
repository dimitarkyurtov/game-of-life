#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define ALIVE 1
#define DEAD 0

// #define DEBUG_ANIMATION
#define RANDOM_DATA

const vector<int> MWSS_PADDED = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const vector<int> HWSS_PADDED = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const vector<int> PULSAR_PADDED = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const vector<int> BEACON = {
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 1, 1,
    0, 0, 1, 1
};

const vector<int> BEACON_PADDED = {
    0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 0, 0,
    0, 0, 0, 1, 1, 0,
    0, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0
};


int count_neighbors(const vector<int> &grid, int x, int y, int N, int local_height, const vector<int>& top_row, const vector<int>& bottom_row) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx < local_height && nx >= 0 && ny < N && ny >= 0) {
                count += grid[nx*N+ny];
            }
            else {
                if (nx == local_height) {
                    if (ny == N) {
                        count += bottom_row[0];
                    }
                    else if (ny == -1) {
                        count += bottom_row[N];
                    }
                    else {
                        count += bottom_row[ny];
                    }
                }
                else if (nx == -1) {
                    if (ny == N) {
                        count += top_row[0];
                    }
                    else if (ny == -1) {
                        count += top_row[N];
                    }
                    else {
                        count += top_row[ny];
                    }
                }
                else if (ny == N) {
                    // case when nx = -1 or nx = local_heigh are handled in previous if statements
                    count += grid[nx*N+0];
                }
                else if (ny == -1) {
                    // case when nx = -1 or nx = local_heigh are handled in previous if statements
                    count += grid[nx*N+(N-1)];
                }
            }
        }
    }
    return count;
}

void print_grid(const vector<int> &grid, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << (grid[i*N+j] ? "1" : ".") << " ";
        }
        cout << endl;
    }
}

void print_vector(const vector<int> &vec) {
    for (const auto& el : vec) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

void print_vector_vector(const vector<vector<int>> &vec) {
    for (const auto& el : vec) {
        for (const auto& el2 : el) {
            std::cout << el2 << " ";
        }
        std::cout << std::endl;
    }
}

#ifdef DEBUG_ANIMATION
void save_grid_to_file(const vector<int> &grid, int N, ofstream &outfile) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            auto s = grid[i*N+j] == ALIVE ? "1" : "0";
            outfile << s;
        }
    }
    outfile << std::endl;
}
#endif

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <grid_size> <num_iterations>" << std::endl;
        }
        return EXIT_FAILURE;
    }

    int N = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int rows_per_proc = N / size;
    vector<int> local_grid(N*N, 0);
    vector<int> new_local_grid(N*N, 0);
    vector<int> initial_grid(N*N, 0);

#ifdef RANDOM_DATA
    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                initial_grid[i*N+j] = rand() % 2;
            }
        }
    }
#endif

#ifdef DEBUG_ANIMATION
    if (rank == 0) {
        initial_grid = MWSS_PADDED;
        // print_vector(initial_grid);
    }

    MPI_Scatter(initial_grid.data(), rows_per_proc * N, MPI_INT,
                local_grid.data(), rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);

    // std::cout << local_grid[1].size() << std::endl;

    ofstream outfile;

    if (rank == 0) {
        outfile.open("gol_animation.txt");
    }
#endif

#ifdef RANDOM_DATA
    srand(time(NULL) + rank);
#endif


#ifdef RANDOM_DATA
    for (int i = 0; i < rows_per_proc; ++i)
        for (int j = 0; j < N; ++j)
            local_grid[i*N+j] = rand() % 2;
#endif

    vector<int> top_row(N), bottom_row(N);

    vector<int> final_grid;
    if (rank == 0) {
        final_grid.resize(N * N);
    }

    for (int iter = 0; iter < iterations; ++iter) {
#ifdef DEBUG_ANIMATION
        MPI_Gather(local_grid.data(), rows_per_proc * N, MPI_INT,
                   final_grid.data(), rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            save_grid_to_file(final_grid, N, outfile);
        }
#endif

        MPI_Sendrecv(local_grid.data(), N, MPI_INT, (rank - 1 + size) % size, 0,
                     bottom_row.data(), N, MPI_INT, (rank + 1) % size, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Sendrecv(local_grid.data() + N*(rows_per_proc - 1), N, MPI_INT, (rank + 1) % size, 0,
                     top_row.data(), N, MPI_INT, (rank - 1 + size) % size, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 0; i < rows_per_proc; ++i) {
            for (int j = 0; j < N; ++j) {
                int live_neighbors = count_neighbors(local_grid, i, j, N, rows_per_proc, top_row, bottom_row);
                if (local_grid[i*N+j] == ALIVE) {
                    new_local_grid[i*N+j] = (live_neighbors == 2 || live_neighbors == 3) ? ALIVE : DEAD;
                } else {
                    new_local_grid[i*N+j] = (live_neighbors == 3) ? ALIVE : DEAD;
                }
            }
        }
        local_grid.swap(new_local_grid);
    }

    #ifdef DEBUG_ANIMATION
        MPI_Gather(local_grid.data(), rows_per_proc * N, MPI_INT,
                   final_grid.data(), rows_per_proc * N, MPI_INT, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            save_grid_to_file(final_grid, N, outfile);
        }
    #endif

    MPI_Finalize();
    return EXIT_SUCCESS;
}
