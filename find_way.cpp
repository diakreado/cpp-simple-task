#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

// recursive function which fill field wave by wave
void fill_field(std::vector<std::vector<int> * > * field, const std::pair<int,int> point) {
  int y = point.first;
  int x = point.second;

  int value = field->at(y)->at(x);

  if (x+1 < field->at(y)->size() && field->at(y)->at(x+1) != -1 && 
      (field->at(y)->at(x+1) == 0 || field->at(y)->at(x+1)  >= value+1)) {
    field->at(y)->at(x+1) = value + 1;
    fill_field(field, std::pair<int,int>(y,x+1));
  }
  if (x-1 >= 0 && field->at(y)->at(x-1) != -1 &&
      (field->at(y)->at(x-1) == 0 || field->at(y)->at(x-1)  >= value+1)) {
    field->at(y)->at(x-1) = value + 1;
    fill_field(field, std::pair<int,int>(y,x-1));
  }
  if (y+1 < field->size() && field->at(y+1)->at(x) != -1 &&
      (field->at(y+1)->at(x) == 0 || field->at(y+1)->at(x)  >= value+1)) {
    field->at(y+1)->at(x) = value + 1;
    fill_field(field, std::pair<int,int>(y+1,x));
  }
  if (y-1 >= 0 && field->at(y-1)->at(x) != -1 &&
      (field->at(y-1)->at(x) == 0 || field->at(y-1)->at(x)  >= value+1)) {
    field->at(y-1)->at(x) = value + 1;
    fill_field(field, std::pair<int,int>(y-1,x));
  }
}

// function use Lee algorithm
std::vector<std::pair<int,int>> * find_way(const std::vector<std::vector<int> * > * field,
                                           const std::pair<int,int> start, const std::pair<int,int> finish) {
  std::vector<std::vector<int> * > * vf = new std::vector<std::vector<int> * >(); // virtual field
  for (auto i : * field) {
    vf->push_back(new std::vector<int>(*i));
  }
  for (auto i : * vf) {
    std::replace(i->begin(), i->end(), 1, -1);
  }
  
  int ySize = vf->size();
  int xSize = vf->at(0)->size();
  
  vf->at(start.first)->at(start.second) = 1;
  fill_field(vf, start);

  std::vector<std::pair<int,int>> * way = new std::vector<std::pair<int,int>>();

  int y = finish.first;
  int x = finish.second;
  if (x < 0 || x >= xSize || y < 0 || y >= ySize ||
      vf->at(y)->at(x) == 0 || vf->at(y)->at(x) == -1 ) {
    return way;
  }

  std::vector<std::pair<int,int>> * way_back = new std::vector<std::pair<int,int>>();

  way_back->push_back(finish);

  std::pair<int,int> current (finish);
  int value = -1;
  while (value != 1) {
    int yc = current.first;
    int xc = current.second;

    value = vf->at(yc)->at(xc);

    if (xc+1 < xSize && vf->at(yc)->at(xc+1) != -1 && vf->at(yc)->at(xc+1) < value) {
      current = std::pair<int,int>(yc,xc+1);
      way_back->push_back(current);
    }
    if (xc-1 >= 0 && vf->at(yc)->at(xc-1) != -1 &&  vf->at(yc)->at(xc-1) < value) {
      current = std::pair<int,int>(yc,xc-1);
      way_back->push_back(current);
    }
    if (yc+1 < ySize && vf->at(yc+1)->at(xc) != -1 && vf->at(yc+1)->at(xc) < value) {
      current = std::pair<int,int>(yc+1,xc);
      way_back->push_back(current);
    }
    if (yc-1 >= 0 && vf->at(yc-1)->at(xc) != -1 && vf->at(yc-1)->at(xc) < value) {
      current = std::pair<int,int>(yc-1,xc);
      way_back->push_back(current);
    }
  }

  int wb_size = way_back->size();
  for (int i = wb_size - 1; i >= 0 ; i--) {
    auto step = way_back->at(i);
    if (i+1 < wb_size && i-1 >= 0) {
      auto next_1 = way_back->at(i-1);
      auto next_2 = way_back->at(i+1);
      if ((step.first  == next_1.first  && step.first  == next_2.first) || 
          (step.second == next_1.second && step.second == next_2.second)) {
        continue;
      }
    }
    way->push_back(step);
  }

  delete way_back;
  for (auto i : *vf) {
    delete i;
  }
  delete vf;

  return way;
  
}

int main() {
  std::vector<std::vector<int> * > * field = new std::vector<std::vector<int> * >();
  field->push_back(new std::vector<int>({0,1,0,0,0}));
  field->push_back(new std::vector<int>({0,1,0,0,0}));
  field->push_back(new std::vector<int>({0,0,0,1,0}));

  auto way = find_way(field, std::pair<int,int>(0,0), std::pair<int,int>(2,4));
  
  for (auto i : *way) {
    std::cout << i.first << " " << i.second << std::endl;
  }
  
  for (auto i : *field) {
    delete i;
  }
  delete field;
  delete way;

  return 0;
}

