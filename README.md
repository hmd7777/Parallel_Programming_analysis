# Parallel Computation Analysis
```bash
git clone https://github.com/your-username/your-repo-name.git

## Overview
This project explores the efficiency of parallel computation in C using different methods. It focuses on counting occurrences of a specific number in an array using various thread counts and array sizes. The key objective is to analyze the performance implications of different parallelization strategies, including the impact of cache optimization.

## Methods
Four parallel computation methods are implemented and analyzed:

- **Race Condition Method**: Implements parallel computation without synchronization mechanisms, leading to race conditions and incorrect results.
- **Mutex Method**: Utilizes mutexes for synchronization to manage access to shared data, ensuring correct results but with potential performance overhead.
- **Private Method**: Each thread uses private variables, eliminating the need for synchronization and avoiding race conditions.
- **Cache Optimization Method**: Aligns each thread's data structure to cache line boundaries to minimize false sharing and improve performance in multi-threaded environments.

## Results
Performance was measured across different array sizes and thread counts for each method. Key findings include:

- **Race Condition Method**: Fastest in terms of execution time but produces incorrect results.
- **Mutex Method**: Provides accurate results with increased execution time due to synchronization overhead.
- **Private Method**: Offers a balance with accurate results and improved performance, especially for larger data sizes.
- **Cache Optimization Method**: Shows significant performance improvement, particularly for larger arrays, by reducing cache coherence issues.
