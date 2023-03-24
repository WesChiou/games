# GameEngine

GameEngine.

### lint with cpplint

```bash
find . -name \*.hpp -or -name \*.cpp | xargs cpplint --filter=-legal/copyright,-whitespace/indent,-whitespace/line_length
```
or (check Makefile first)
```bash
make lint
```
