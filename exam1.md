# Langauges Exam 1 Notes

* Models of Computation
* Procedural
* Functional
* Logic
* Object-Oriented

## Models
1. What are 3 models of computation?
1. Why is there so much research into quantum computers?

## Procedural
1. Why would you write a operations manual for
a canal system in procedural style?
1. What are good reasons to use procedural style?
1. Even though this uses a C++ function, why is this not functional style programming:
```C++
void convert(double f) {
    double c = (5.0/9.0)*(f-32.0);
    cout << f << " deg F is " 
         << c << " deg C" << std:endl;
}
```

## Functional 
1. Why is SQL not a procedural style language?

1. Why is functional style connected to immutable objects?

1. Why would you choose a language that is strictly functional style instead of a general purpose language?

1. Convert the `convert` to functional style.

1. What are advantages of functional style programming?

# Logic / Contraint

1. Why are essentially all UI layout languages constraint languages?

1. Why is logic style a terrible idea for an emergency response procedure manual?

1. What are advantages of logic style programming?

1. How would you modify the follwing prolog so the query would include 'peanuts'?

```
like(mike,cheese).
like(mike,eggs).
like(mike,peanuts).
like(sue,bike).
like(sue,kites).
likes(Thing) :- like(mike,Thing), like(sue,Thing).

likes(Thing).
```

1. Why is SQL a logic language?

## Security

1. Why is lack of public/private a security concern in a language?
1. JSON & XML are data languages for communication between systems.  Why are these not general purpose languages?
1. C++ is high performance, but allows for memory problems such as buffer overflow.  Java and C# always check.  Why are low level tools like video decoders written in C/C++ and service tools API's for, say amazon orders, are written in Java?
1. You are asked to build a web service for the internet-of-things where each switch and light bulb in a corporation is controllable from the system.  What language(s) would you choose and why?
1. Now you work at Levi's and builing their order fullfillment system.  Now what?
1. Why does Apple not allow scripting languages in their App store?
