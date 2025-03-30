#include <bits/stdc++.h>
#include "../Models/RubiksCubeAbstract.h"

#ifndef RUBIKS_CUBE_SOLVER_BFS_SOLVER_H
#define RUBIKS_CUBE_SOLVER_BFS_SOLVER_H

template<typename State, typename Hash>
class bfs_solver {
public:
    State rubiks_cube;

    bfs_solver(State initial_cube) {
        rubiks_cube = initial_cube;
    }

    vector<RubiksCube::MOVE> solve() {
        State solved_state = perform_bfs();
        assert(solved_state.is_solved());

        State current_state = solved_state;
        while (!(current_state == rubiks_cube)) {
            RubiksCube::MOVE last_move = previous_moves[current_state];
            move_sequence.push_back(last_move);
            current_state.invert(last_move);
        }

        rubiks_cube = solved_state;
        reverse(move_sequence.begin(), move_sequence.end());
        return move_sequence;
    }

private:
    vector<RubiksCube::MOVE> move_sequence;
    unordered_map<State, bool, Hash> visited_states;
    unordered_map<State, RubiksCube::MOVE, Hash> previous_moves;

    State perform_bfs() {
        queue<State> state_queue;
        state_queue.push(rubiks_cube);
        visited_states[rubiks_cube] = true;

        while (!state_queue.empty()) {
            State current_state = state_queue.front();
            state_queue.pop();

            if (current_state.is_solved()) {
                return current_state;
            }

            for (int move_index = 0; move_index < 18; move_index++) {
                auto move = RubiksCube::MOVE(move_index);
                current_state.move(move);

                if (!visited_states[current_state]) {
                    visited_states[current_state] = true;
                    previous_moves[current_state] = move;
                    state_queue.push(current_state);
                }

                current_state.invert(move);
            }
        }

        return rubiks_cube;
    }
};

#endif