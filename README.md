<p align="center">
<img src="https://github.com/daviduartecf/push_swap/blob/main/swap.png" style="width: 12%;">
</p>
<h1 align="center">PIPEX</h1>

<p align="center"> <strong>Pipex</strong> is a project from the 42 school that mimics the behaviour of the following shell command:</p>

```
< file1 cmd1 | cmd2 > file2
```
The program takes four arguments:

    file1: The name of the input file.
    cmd1: The first shell command (with parameters).
    cmd2: The second shell command (with parameters).
    file2: The name of the output file.


<p align="center">
  <a href="https://github.com/daviduartecf/pipex/blob/main/pipexsubject.pdf">
    <img src="https://emojicdn.elk.sh/📖" width="20" alt="Book emoji">
    <br>
    Read the subject
  </a>
</p>

## Installation and Usage intructions
1. Clone the repository:
    ```sh
    git clone git@github.com:daviduartecf/pipex.git
    ```
2. Compile the project:
    ```sh
    make
    ```
3. Run the executable:
    ```sh
    ./pipex infile "ls -l" "wc -l" outfile
    ```
