#include <algorithm>
#include <iostream>
#include <optional>
#include "../include/State.hpp"

StateManager::StateManager() {
  std::cout << "StateManager" << std::endl;
}

StateManager::~StateManager() {
  for (auto v : state_nodes) {
    v.state->unload();
  }
  state_nodes.clear();
  std::cout << "~StateManager" << std::endl;
}

void StateManager::handle_event(SDL_Event& event) {
  size_t tmp = state_nodes.size();
  for (int i = 0; i < tmp && i < state_nodes.size(); i++) {
    if (state_nodes[i].should_handle_event) {
      state_nodes[i].state->handle_event(event, *this);
    }
  }
}

void StateManager::update() {
  state_nodes.erase(std::remove_if(state_nodes.begin(), state_nodes.end(),
    [](const StateNode& node) {
      return node.need_to_fuse;
    }),
  state_nodes.end());

  size_t tmp = state_nodes.size();
  for (int i = 0; i < tmp && i < state_nodes.size(); i++) {
    if (state_nodes[i].should_update) {
      state_nodes[i].state->update();
    }
  }
}

void StateManager::render() {
  size_t tmp = state_nodes.size();
  for (int i = 0; i < tmp && i < state_nodes.size(); i++) {
    if (state_nodes[i].should_render) {
      state_nodes[i].state->render();
    }
  }
}

void StateManager::edit_state(std::string unique_name, StateConfig config) {
  for (int i = 0; i < state_nodes.size(); i++) {
    if (state_nodes[i].unique_name == unique_name) {
      state_nodes[i].should_handle_event = config.should_handle_event;
      state_nodes[i].should_update = config.should_update;
      state_nodes[i].should_render = config.should_render;
      state_nodes[i].need_to_fuse = config.need_to_fuse;
      break;
    }
  }
}

void StateManager::add_state(StateNode node) {
  // Replace existed (by unique_name).
  for (int i = 0; i < state_nodes.size(); i++) {
    if (state_nodes[i].unique_name == node.unique_name) {
      state_nodes[i].state->unload();
      state_nodes[i] = node;
      node.state->load();
      return;
    }
  }

  // Or, push_back it.
  state_nodes.push_back(node);
  node.state->load();
}
