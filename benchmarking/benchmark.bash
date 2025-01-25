# echo 1 process
# echo Attempt 1
# time mpirun -np 1 ./game-of-life 600 10000
# echo
# echo Attempt 2
# time mpirun -np 1 ./game-of-life 600 10000
# echo
# echo Attempt 3
# time mpirun -np 1 ./game-of-life 600 10000
# echo

# echo 2 process
# echo Attempt 1
# time mpirun -np 2 ./game-of-life 600 10000
# echo
# echo Attempt 2
# time mpirun -np 2 ./game-of-life 600 10000
# echo
# echo Attempt 3
# time mpirun -np 2 ./game-of-life 600 10000
# echo

# echo 3 process
# echo Attempt 1
# time mpirun -np 3 ./game-of-life 600 10000
# echo
# echo Attempt 2
# time mpirun -np 3 ./game-of-life 600 10000
# echo
# echo Attempt 3
# time mpirun -np 3 ./game-of-life 600 10000
# echo

# echo 4 process
# echo Attempt 1
# time mpirun -np 4 ./game-of-life 600 10000
# echo
# echo Attempt 2
# time mpirun -np 4 ./game-of-life 600 10000
# echo
# echo Attempt 3
# time mpirun -np 4 ./game-of-life 600 10000

echo 6 process
echo Attempt 1
time mpirun -np 6 ./game-of-life 600 10000
echo
echo Attempt 2
time mpirun -np 6 ./game-of-life 600 10000
echo
echo Attempt 3
time mpirun -np 6 ./game-of-life 600 10000

echo 8 process
echo Attempt 1
time mpirun -np 8 ./game-of-life 600 10000
echo
echo Attempt 2
time mpirun -np 8 ./game-of-life 600 10000
echo
echo Attempt 3
time mpirun -np 8 ./game-of-life 600 10000