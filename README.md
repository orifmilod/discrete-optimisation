# Discrete optimisation
[Discret optimization](https://en.wikipedia.org/wiki/Combinatorial_optimization) techniques applied on different combinatorial problems.

## Problems implemented
[Graph-coloring](#graph-coloring) <br/>
[Knapsack](#knapsack)  <br/>
[Travelling salesman](#travelling-salesman) <br/>

###Graph-coloring (aka map-coloring)
Problem statement: The basic idea is to color a graph in which no two connected nodes share the same colors. The challenge is to find the minumim number of colors needed to color the graph (chromatic number)

<img src="https://user-images.githubusercontent.com/25881325/114223955-bc54e800-9970-11eb-92bb-61ac987abdb1.png" heigh='300px' width='300px'/>
Currently solved using these approaches: 

- [X] [Greedy](https://en.wikipedia.org/wiki/Greedy_coloring#:~:text=In%20the%20study%20of%20graph,vertex%20its%20first%20available%20color) - Just pick the first available color and proceed to the neighbour, backtrack if not feasible.
- [X] [D-satur](https://en.wikipedia.org/wiki/DSatur) - Color most saturated verices then proceed to neigbours.
      <br/> <li> Great paper by Technical University of Gdansk about [D-Satur algorithm](https://core.ac.uk/download/pdf/82314213.pdf) </li>    
- [ ] [VAS(Variable neighborhood search)](https://en.wikipedia.org/wiki/Variable_neighborhood_search#Introduction) 

### Knapsack
Problem statement: Given a set of items, each with a weight and a value, determine the number of each item to include in a collection so that the total weight is less than or equal to a given limit and the total value is as large as possible
<img src="https://user-images.githubusercontent.com/25881325/114224600-91b75f00-9971-11eb-8d62-f5f783c1d345.jpeg" width='400px'/>

Currently solved using these approaches: 

- [X] [Dynamic-programming](https://en.wikipedia.org/wiki/Dynamic_programming)
