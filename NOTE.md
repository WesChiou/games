```Makefile
my_target: dependency1 dependency2
  command $^ -o $@
```

$^ 表示所有依赖项，即 dependency1 和 dependency2
$@ 表示目标，即 my_target
$< 表示第一个依赖项，即 dependency1

```c++
#ifndef INCLUDE_STATE_HPP_
#define INCLUDE_STATE_HPP_

#include <SDL2/SDL.h>
#include <functional>

class State
{
public:
  bool should_update{ true };
  bool should_render{ true };
  bool should_handle_event{ true };
  std::function<void ()> enter;
  std::function<void ()> update;
  std::function<void (SDL_Renderer*)> render;
  std::function<void (SDL_Event*)> handle_event;
  std::function<void ()> exit;
};

#endif  // INCLUDE_STATE_HPP_
```


Entity


Component
  土壤
  水
  石头
  石
  肥力
  板结程度

System
  取名系统
    泥和水混合，根据比例，可以是“泥浆”、“浑水”、“潮湿的泥土”等
  流动系统
    松软的土会流一部分到四周，水会流到四周和渗入地下，温度会随着物体的转移发生一些转移
  交互系统
    重物冲击泥土会增加土壤板结；蚯蚓死亡会增加土壤肥力；动物踩踏含水高的泥土会形成泥浆
  生物生命周期系统
    存活条件判断，例如高温导致枯死，土壤板结导致蚯蚓死亡；生长速率，例如根系所在土壤肥力和水分共同决定生长速率；种子萌芽条件等
  生物行为系统
    土壤板结超过某个阈值蚯蚓会向四周转移，蝴蝶会围绕花飞行
  结构系统
    相邻单元里的石头视为一个整块，一个木头可能占地很多个格子
  转化系统
    气态水转液态水


```C++
class Cell;

// World2D
class World2D {
public:
  World2D(uint32_t cols, uint32_t rows) : cols(cols), rows(rows) {
    cells = std::vector<Cell>(this->cols * this->rows);
  }

  std::optional<Cell> get_cell(uint32_t col, uint32_t row) {
    uint32_t index = col + row * cols;
    if (index < cells.size()) {
      return cells[index];
    }
    return std::nullopt;
  }

private:
  uint32_t cols{ 0 };
  uint32_t rows{ 0 };

  std::vector<Cell> cells;
};

// World3D
class World3D {
public:
  World3D(uint32_t x, uint32_t y, uint32_t z) : size_x(x), size_y(y), size_z(z) {
    cells = std::vector<Cell>(size_x * size_y * size_z);
  }

  std::optional<Cell> get_cell(uint32_t x, uint32_t y, uint32_t z) {
    uint32_t index = x + y * size_x + z * (size_x * size_y);
    if (index < cells.size()) {
      return cells[index];
    }
    return std::nullopt;
  }

private:
  uint32_t size_x{ 0 };
  uint32_t size_y{ 0 };
  uint32_t size_z{ 0 };

  std::vector<Cell> cells;
};
```

```json
{
  "id": 1,
  "image_type": 1, // 1-png
  "filepath": "res/grass_tileset_16x16/grass_tileset_16x16.png",
  "srcrect": [96, 0, 16, 16],
  "description": "ground tile 1",
}
```

```C++
int random_int(int rng1, int rng2) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(rng1, rng2);
  return dist6(rng);
}
```
