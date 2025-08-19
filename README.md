# vcc

`vcc` is a simple version control system inspired by Git. It allows you to track changes to files in your project, commit snapshots, and manage file history.

---

## Features

* **Initialize a repository**: Start a new repository in the current directory.
* **Add files**: Stage individual files or all files at once.
* **Remove files**: Unstage or remove files from the repository.
* **Commit changes**: Save a snapshot of the current state with a commit message.

---

## Commands

### `vcc init`

Initialize a new repository in the current directory. This will create a `.vcc` directory to store all repository data.

```bash
vcc init
```

---

### `vcc add <file>` or `vcc add .`

Add files to the staging area (index). You can specify a single file:

```bash
vcc add file.txt
```

Or add all files in the current directory:

```bash
vcc add .
```

---

### `vcc rm <file>`

Remove a file from the staging area (or repository):

```bash
vcc rm file.txt
```

---

### `vcc commit -m "message"`

Commit the staged changes with a message. The `-m` flag is required to specify the commit message:

```bash
vcc commit -m "Initial commit"
```

* Each commit stores the current snapshot of the repository.
* Commits are linked, allowing you to track the history of your project.

---

## Directory Structure

After running `vcc init`, your repository will have the following structure:

```
.vcc/
├── objects/     # Stores file and commit objects
├── refs/        # Stores branch references
└── HEAD         # Points to the current branch
```

