#include "graph.h"

void Graph::insert(string s_type, string s_name, vector<string> inputs, vector<string> outputs, vector<string> in_args) {

  Layer * new_layer = nullptr;
  if (s_type.compare("debug") == 0) {
    new_layer = new Debug(s_name, inputs, outputs, in_args);
  }
  else if (s_type.compare("data") == 0) {
    new_layer = new Data(s_name, inputs, outputs, in_args);
  }
  
  directory[new_layer->name] = new_layer;
}

void Graph::find_path(string in_path) {
   
  std::stack<string> top_sort;
  std::stack<string> frontier;

  frontier.push(in_path);

  while(!frontier.empty()) {
    string curr = frontier.top();
    frontier.pop();
    vector<string> next = directory[curr]->prev;
    for(int i = 0; i < next.size(); i++) {
      if(next[i].compare("NULL") != 0) {
        frontier.push(next[i]);
      }
    }
    top_sort.push(curr);
  }
  
  curr_path = top_sort;

}

Matrix Graph::forward() {
  std::stack<string> path_cpy = curr_path;

  std::stack<Matrix> buffer;
  Layer *curr_layer = nullptr;
  string curr;

  while(!path_cpy.empty()) {
    curr = path_cpy.top();
    path_cpy.pop();
    curr_layer = directory[curr];
    Matrix out;
   
    if (curr_layer->prev.size() == 1) {
      out = curr_layer->forward(out);
    } else if (curr_layer->prev.size() == 2) {
      out = buffer.top();
      buffer.pop();
      out = curr_layer->forward(out);
    }
    buffer.push(out);

  }

  return buffer.top();
}


