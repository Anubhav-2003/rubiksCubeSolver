#include <bits/stdc++.h>
#include "../Models/RubiksCubeAbstract.h"

#ifndef RUBIKS_CUBE_SOLVER_IDA_STAR_SOLVER_H
#define RUBIKS_CUBE_SOLVER_IDA_STAR_SOLVER_H

template<typename CubeState, typename HashFunction>
class ida_star_solver {
private:
    CornerPatternDatabase corner_db;
    vector<RubiksCube::MOVE> solution_moves;
    unordered_map<CubeState, RubiksCube::MOVE, HashFunction> last_move_used;
    unordered_map<CubeState, bool, HashFunction> seen_states;

    struct search_node {
        CubeState cube_config;
        int move_count;
        int heuristic_cost;

        search_node(CubeState _cube_config, int _move_count, int _heuristic_cost)
            : cube_config(_cube_config), move_count(_move_count), heuristic_cost(_heuristic_cost) {}
    };

    struct node_comparator {
        bool operator()(const pair<search_node, int>& a, const pair<search_node, int>& b) {
            auto node_a = a.first, node_b = b.first;
            if (node_a.move_count + node_a.heuristic_cost == node_b.move_count + node_b.heuristic_cost) {
                return node_a.heuristic_cost > node_b.heuristic_cost;
            }
            return node_a.move_count + node_a.heuristic_cost > node_b.move_count + node_b.heuristic_cost;
        }
    };

    void clear_search_data() {
        solution_moves.clear();
        last_move_used.clear();
        seen_states.clear();
    }

    pair<CubeState, int> run_ida_star(int depth_limit) {
        priority_queue<pair<search_node, int>, vector<pair<search_node, int>>, node_comparator> search_queue;
        search_node start_node = search_node(initial_cube, 0, corner_db.getNumMoves(initial_cube));
        search_queue.push(make_pair(start_node, 0));
        int next_depth_limit = INT_MAX;

        while (!search_queue.empty()) {
            auto [current_node, move_index] = search_queue.top();
            search_queue.pop();

            if (seen_states[current_node.cube_config]) continue;

            seen_states[current_node.cube_config] = true;
            last_move_used[current_node.cube_config] = RubiksCube::MOVE(move_index);

            if (current_node.cube_config.is_solved()) {
                return make_pair(current_node.cube_config, depth_limit);
            }

            current_node.move_count++;
            for (int move_id = 0; move_id < 18; move_id++) {
                auto move_to_apply = RubiksCube::MOVE(move_id);
                current_node.cube_config.move(move_to_apply);

                if (!seen_states[current_node.cube_config]) {
                    current_node.heuristic_cost = corner_db.getNumMoves(current_node.cube_config);
                    if (current_node.heuristic_cost + current_node.move_count > depth_limit) {
                        next_depth_limit = min(next_depth_limit, current_node.heuristic_cost + current_node.move_count);
                    } else {
                        search_queue.push(make_pair(current_node, move_id));
                    }
                }

                current_node.cube_config.invert(move_to_apply);
            }
        }

        return make_pair(initial_cube, next_depth_limit);
    }

public:
    CubeState initial_cube;

    ida_star_solver(CubeState cube_state, string database_file) {
        initial_cube = cube_state;
        corner_db.fromFile(database_file);
    }

    vector<RubiksCube::MOVE> find_solution() {
        int depth_limit = 1;
        auto search_result = run_ida_star(depth_limit);

        while (search_result.second != depth_limit) {
            clear_search_data();
            depth_limit = search_result.second;
            search_result = run_ida_star(depth_limit);
        }

        CubeState solved_state = search_result.first;
        assert(solved_state.is_solved());

        CubeState current_state = solved_state;
        while (!(current_state == initial_cube)) {
            RubiksCube::MOVE applied_move = last_move_used[current_state];
            solution_moves.push_back(applied_move);
            current_state.invert(applied_move);
        }

        initial_cube = solved_state;
        reverse(solution_moves.begin(), solution_moves.end());
        return solution_moves;
    }
};

#endif
