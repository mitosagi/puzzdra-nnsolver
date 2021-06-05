# パズドラ 機械学習ソルバ

## Compile

```
g++ -O2 -std=c++11 -fopenmp puzz_api.cpp -o puzz_api
./puzz_api

c++ -O3 -Wall -shared -std=c++11 -I/usr/include/python3.6m -Iextern/pybind11/include -fopenmp -fPIC $(python3 -m pybind11 --includes) puzzpy.cpp -o puzzpy$(python3-config --extension-suffix)

pip3 install -e .
```

## License
[koduma/puzzdra_solver](https://github.com/koduma/puzzdra_solver): コンボ計算部を評価関数として使用
