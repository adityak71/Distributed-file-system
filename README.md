===========================================
     MINI DISTRIBUTED FILE SYSTEM (WEB / TERMINAL)
===========================================

Project Type: Web Simulation or CLI using C++
Technologies Used: HTML, CSS, JavaScript, C++
Author: Aditya Kumar
College: Lovely Professional University
-------------------------------------------

ABOUT THE PROJECT
-------------------------------------------
This project is a simple simulation of a 
Distributed File System (DFS), built in two versions:
1. A web-based simulation using HTML, CSS, and JavaScript.
2. A terminal-based version using C++.
3. Open exe file to directly open the CLI version

The system shows how files are stored across multiple 
nodes (computers), how data replication works, and 
how the system repairs missing files when a node 
fails or recovers.

It helps to understand important distributed system 
concepts like fault tolerance, replication, and recovery 
used in real-world systems such as:
- Google File System (GFS)
- Hadoop Distributed File System (HDFS)

-------------------------------------------
FEATURES
-------------------------------------------
1. Upload and download files easily.
2. Store multiple copies of each file 
   (replication factor for safety).
3. Simulate node failure and recovery.
4. Repair missing files automatically.
5. View file distribution across all nodes.

-------------------------------------------
WHAT IS A NODE?
-------------------------------------------
A Node represents one storage unit 
(like a small computer or server).

Each node can:
- Store files.
- Be active (working) or down (failed).
- Recover later and rejoin the system.

Even if one node fails, the file remains 
available from other nodes that hold its copy.

-------------------------------------------
HOW IT WORKS
-------------------------------------------
1. The system starts with 4 nodes.
2. Replication factor is set to 2.
   (Every file is copied to 2 different nodes)
3. If a node fails, its data stays safe on 
   another active node.
4. The "Repair Faults" feature restores lost 
   files when nodes recover.

-------------------------------------------
HOW TO RUN THE PROJECT
-------------------------------------------

For the Web Version:
1. Download or copy the project folder.
2. Open the file named "index.html" in any 
   web browser.
3. Use the on-screen buttons to:
   - Upload a file
   - Download a file
   - Fail or Recover nodes
   - Repair lost files
   - View file distribution

For the Terminal (C++) Version:
1. Open the C++ file in any IDE or text editor.
2. Open the exe file directly to use in CLI. 
2. Compile and run it using a C++ compiler.
3. Follow the menu-based instructions in the terminal.

-------------------------------------------
FILES INCLUDED
-------------------------------------------
1. index.html    	 → Web structure and layout
2. style.css     	 → Design and color styling
3. script.js     	 → JavaScript logic (simulation)
4. dfs.cpp       	 → C++ CLI version of the system
5. README.txt    	 → Project documentation
6. about_project.docx 	 → a Description of project 

-------------------------------------------
FREQUENTLY ASKED QUESTIONS (FAQs)
-------------------------------------------

Q1: What is the purpose of this project?
Ans: To understand how distributed file systems 
store data, handle node failures, and recover data.

Q2: Can it store real files?
Ans: No, this is a simulation. It stores 
only text data in memory for demonstration.

Q3: What is replication?
Ans: Replication means keeping multiple copies 
of the same file on different nodes for safety.

Q4: What happens if all nodes fail?
Ans: No files can be accessed until at least 
one node becomes active again.

Q5: Can I change the number of nodes or replicas?
Ans: Yes. You can modify this line in JavaScript:
    const dfs = new DistributedFileSystem(4, 2);
   The first number = total nodes.
   The second number = replication factor.
   And same as c ++ you can change this line.

-------------------------------------------
AUTHOR
-------------------------------------------
Name: Aditya Kumar
Course: Computer Science Engineering
Institute: Lovely Professional University
Email: adityak201811@gmail.com
-------------------------------------------

THANK YOU FOR VIEWING MY PROJECT
===========================================
