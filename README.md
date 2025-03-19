# EXPRESSION 

## Build

```sh
mkdir build
cd build 
cmake -DCMAKE_BUILD_TYPE=Release ..
make 
```
## Run tests 

```sh
make test
```

## Differentiator

```sh
differentiator --eval “x * y“ x=10 y=12
```
```sh
differentiator --diff “x * sin(x)“ --by x
```