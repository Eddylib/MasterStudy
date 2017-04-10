# Boost Library Codes

A subdirectory to learn Boost ---- a c++ library encapsulates most features of various system.

* thread.cpp shows codes that depict the features of thread.All work well on Ubuntu 14.04
* condition shows codes about a reader-writer problem.



`condition.cpp`
------------

* A condition must exist with a mutex, which is a lock to protect the attrbutes of
  condition.
* If a condition protect a data struct just in the areas of the condition code. any
  other attributes of the dada struct must be proected with other measures.(here i
  used a queue in std lib. the push and pop can be protected but the attr of the queue
  itself not. So, the attr lock did this. If I build a thread safe queue, there is no
  need of the attrlock)
* for multy readers and writers, the if must be changed to where when judge either the queue
  is full or empty.

