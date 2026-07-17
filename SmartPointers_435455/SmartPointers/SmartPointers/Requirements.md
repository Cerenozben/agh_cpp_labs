# SmartPointers

&nbsp;

## **ProducerConsumer**

### **Prototype should be done in ProducerConsumer.h**

### **Implementation should be done in ProducerConsumer.cpp**

The class initializes initial values such as number of items produced, delay between productions, delay for consumer A and consumer B. The start() method starts three threads: producer, consumer A, and consumer B. The "producer" produces a certain number of items and places them in a queue. Consumers check the queue in a loop and fetch items if available. If the queue is empty and production has finished, then consumers exit. After each production or consumption operation, the program waits for a specified delay to simulate real time. Threads are synchronized using mutexes to avoid problems accessing shared resources. When production finishes, the productionFinished\_ flag is set to true, which causes consumers to terminate when the queue runs out of items.

In Details, the ProducerConsumer class consists of the following elements:

- Define a class named "ProducerConsumer" inside the "smartPointers" namespace.
- A constructor that takes 4 arguments:
  - numProducedItems - the number of items to produce.
  - productionDelay - the delay between productions.
  - consumerADelay - the delay for consumer A.
  - consumerBDelay - the delay for consumer B.
- A start() method that creates threads for the producer and two consumers.
- Private fields of the class:
  - numProducedItems\_ - the number of items to produce.
  - productionDelay\_ - the delay between productions.
  - consumerADelay\_ - the delay for consumer A.
  - consumerBDelay\_ - the delay for consumer B.
  - queue\_ - the queue to which the producer adds items, and from which the consumers retrieve them. Queue have inside production numbers as int.
  - queue*mutex* - a mutex for synchronizing access to the queue.
  - cout*mutex* - a mutex for synchronizing access to the standard output.
  - productionFinished\_ - a flag indicating whether production has been completed.
- Private methods of the class:
  - producer() - the producer adds items to the queue in a loop, with a delay between each production. The producer() method performs the following steps:
    - It starts a for loop that will execute numProducedItems\_ times, which means it will add exactly that many items to the queue.
    - It puts the thread to sleep for a time specified by the productionDelay\_ variable. This creates a delay that simulates the production time.
    - The production time doesn't block any mutex.
    - It prints "Produced {int}\n" to the console, where int is the number of the produced item. Remember to use the cout*mutex* for synchronization.
    - It adds the number of the produced item to the queue. Remember to use the queue*mutex* for synchronization.
    - After completing all iterations, it sets the productionFinished\_ flag.
  - consumer(const std::string & type, const std::chrono::milliseconds delay) The consumer() method performs the following steps:
    - The function starts with an infinite loop that contains the entire body of the function.
    - The function checks if the queue is not empty.
      - If it's not empty, it takes a value from it.
      - If the queue is empty, it checks if productionFinished\_ is true. If it is, it breaks out of the infinite loop.
      - Remember to use the queue*mutex*.
    - If a value has been taken from the queue, the consumption takes place.
      - It puts the thread to sleep for a time specified by the "delay" argument to simulate consumption time.
      - The consumption time does not block any mutex.
      - After the consumption is finished, the function prints to the console "Consumer {name} consumed {item}\n", where name is the name of the consumer (A or B) and item is the number consumed from the queue.

### TestProducerConsumer at this point should work

## **GraphNode**

### **Implementation should be done in Graph.h**

- Provide forward declaration of GraphNode.
- Declare alias "GraphNodePtr" for std::shared_ptr<GraphNode>
- Define a class named "GraphNode" inside the "smartPointers" namespace.
- Add a private field named "label\_" of type string to the class.
- Add a private vector of shared*ptr pointers to objects of the "GraphNode" class named "edges*" to the class.
- Define a constructor for the class that takes a label for the graph node as an argument and initializes the "label\_" field.
- Define a method named "addEdge" that takes a GraphNodePtr as an argument and adds it to the "edges\_" vector.
- Define a public method named "getLabel" that returns the label of the graph node.
- Define a public method named "getEdges" that returns a vector of shared_ptr pointers to nodes connected to the graph node.

### TestGraphNode at this point should work

&nbsp;

## **Graph**

### **Implementation should be done in Graph.h**

- Add a class named "Graph" inside the "smartPointers" namespace.
- Add one private vector of GraphNodePtr named "nodes\_" to the class.
- Add a method named "addNode" that takes a GraphNodePtr as an argument and adds it to the "nodes\_" vector.
- Add a public method named "getNodes" that returns a const nodes\_.

### TestBasicGraph at this point should work

### **Prototype should be done in Graph.h**

### **Implementation should be done in Graph.cpp**

- Add a method named "addEdge" that takes two strings arguments being a node labels.
- If at least one node does not exist, the function should add it

### TestAddEdge at this point should work

### **Prototype should be done in Graph.h**

### **Implementation should be done in Graph.cpp**

- look at: <https://mermaid.js.org/syntax/flowchart.html#graph>
- look at: <https://mermaid.live/>
- Implement the toMermaid() method for the Graph class.
- This method should return a textual representation of the graph in the syntax of the Mermaid language.
- This method should be const.
- Graph should define directed flowchart.
- The flowchart should be of type LR (left to right).
- The method should return a string, not print it to the screen.

### TestToMermaid at this point should work

- Implement the fromMermaid() method for the Graph class.
- The fromMermaid method should take a string parameter, which is a Mermaid-formatted string that represents the graph.
- The method should fill Graph object and add nodes and edges to it according to the Mermaid string.
- The method should handle the nodes and edges. And be compatible with toMermaid method.
- Use std::regex inside.

### TestFromMermaid at this point should work
