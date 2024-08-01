<h1>Deadlock Prevention in Resource Allocation</h1>
    This project demonstrates a simple deadlock prevention mechanism using the Resource Allocation Graph (RAG) model in C++. The implementation manages the allocation and release of resources among multiple processes to avoid deadlocks.
    <h2>Overview</h2>
    The <code>ResourceManager</code> class manages the allocation and release of resources to different processes. It uses a mutex and a condition variable to synchronize access to resources and prevent deadlocks.
    <h3>Features</h3>
    <ul>
        <li><strong>Resource Requesting</strong>: Processes can request resources, and the system grants them if available.</li>
        <li><strong>Resource Releasing</strong>: Processes release resources back to the system once done.</li>
        <li><strong>Deadlock Prevention</strong>: By checking resource availability before granting requests, the system prevents potential deadlocks.</li>
    </ul>
    <h2>How It Works</h2>
    <ol>
        <li><strong>Initialization</strong>: The system initializes with a set of total resources and multiple processes with their respective resource requests.</li>
        <li><strong>Resource Request</strong>: Processes request resources, and the system checks if the resources can be allocated without causing a deadlock.</li>
        <li><strong>Resource Allocation</strong>: If resources are available, they are allocated to the requesting process.</li>
        <li><strong>Resource Release</strong>: After completing their work, processes release the resources back to the system.</li>
        <li><strong>Synchronization</strong>: Mutex and condition variables are used to ensure thread-safe operations.</li>
    </ol>
    <h2>Example</h2>
    <p>When you run the program, you'll be prompted to enter:</p>
    <ul>
        <li>The number of different resources.</li>
        <li>The total amount of each resource.</li>
        <li>The number of processes.</li>
        <li>The resource request for each process.</li>
    </ul>
    <p>The system will then simulate resource allocation and release, showing the status of each process and the resources at each step.</p>
    <h2>Code Structure</h2>
    <ul>
        <li><strong><code>ResourceManager</code> Class</strong>: Handles resource management, including requesting and releasing resources.</li>
        <li><strong><code>process</code> Function</strong>: Simulates a process requesting and using resources.</li>
        <li><strong><code>main</code> Function</strong>: Sets up the environment and starts the processes.</li>
    </ul>
  
