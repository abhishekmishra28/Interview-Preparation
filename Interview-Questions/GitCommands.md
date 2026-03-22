# 📘 The Complete Guide to Git and Its Commands

---

## 📑 Table of Contents

1. [Introduction to Git](#introduction-to-git)
2. [Installation](#installation)
3. [Git Configuration](#git-configuration)
4. [Repository Basics](#repository-basics)
5. [Staging and Committing](#staging-and-committing)
6. [Branching and Merging](#branching-and-merging)
7. [Remote Repositories](#remote-repositories)
8. [Inspecting and Comparing](#inspecting-and-comparing)
9. [Undoing Changes](#undoing-changes)
10. [Stashing](#stashing)
11. [Tagging](#tagging)
12. [Rebasing](#rebasing)
13. [Cherry-Picking](#cherry-picking)
14. [Submodules](#submodules)
15. [Git Aliases](#git-aliases)
16. [Advanced Commands](#advanced-commands)
17. [Git Best Practices](#git-best-practices)
18. [Git Workflow Models](#git-workflow-models)
19. [Cheat Sheet](#cheat-sheet)

---

## Introduction to Git

**Git** is a free, open-source **distributed version control system** (DVCS) designed to handle everything from small to very large projects with speed and efficiency.

### Why Use Git?

- ✅ Track changes in your code
- ✅ Collaborate with other developers
- ✅ Maintain a history of your project
- ✅ Work on multiple features simultaneously using branches
- ✅ Revert to previous versions of your code
- ✅ Work offline and sync later

### Key Concepts

| Concept | Description |
|---------|-------------|
| **Repository (Repo)** | A directory that contains your project files and the `.git` folder |
| **Commit** | A snapshot of your project at a point in time |
| **Branch** | An independent line of development |
| **Staging Area (Index)** | A space where changes are prepared before committing |
| **Working Directory** | The files you see in your project folder |
| **Remote** | A version of your repository hosted on the internet or network |
| **Clone** | A copy of a repository |
| **HEAD** | A pointer to the current branch/commit you're on |

### The Three States of Git

```
Working Directory  →  Staging Area (Index)  →  Repository (.git)
     (modify)            (stage)                 (commit)
```

---

## Installation

### Windows

```bash
# Download from https://git-scm.com/download/win
# Or use winget
winget install --id Git.Git -e --source winget

# Or use Chocolatey
choco install git
```

### macOS

```bash
# Using Homebrew
brew install git

# Or using Xcode Command Line Tools
xcode-select --install
```

### Linux

```bash
# Debian/Ubuntu
sudo apt-get update
sudo apt-get install git

# Fedora
sudo dnf install git

# Arch Linux
sudo pacman -S git

# CentOS/RHEL
sudo yum install git
```

### Verify Installation

```bash
git --version
```

> **Output:** `git version 2.42.0` (version may vary)

---

## Git Configuration

Git configuration is managed at three levels:

| Level | Flag | File Location | Description |
|-------|------|---------------|-------------|
| **System** | `--system` | `/etc/gitconfig` | Applies to all users |
| **Global** | `--global` | `~/.gitconfig` | Applies to the current user |
| **Local** | `--local` | `.git/config` | Applies to the current repository |

### Setting Up Identity

```bash
# Set your name
git config --global user.name "Your Name"

# Set your email
git config --global user.email "youremail@example.com"
```

### Setting Default Editor

```bash
# VS Code
git config --global core.editor "code --wait"

# Vim
git config --global core.editor "vim"

# Nano
git config --global core.editor "nano"

# Sublime Text
git config --global core.editor "subl -n -w"
```

### Setting Default Branch Name

```bash
git config --global init.defaultBranch main
```

### Line Ending Configuration

```bash
# Windows
git config --global core.autocrlf true

# macOS/Linux
git config --global core.autocrlf input
```

### Viewing Configuration

```bash
# List all configurations
git config --list

# List with showing the origin/source
git config --list --show-origin

# Get a specific config value
git config user.name

# Edit global config file directly
git config --global --edit
```

### Useful Configuration Options

```bash
# Enable colorful output
git config --global color.ui auto

# Set default merge tool
git config --global merge.tool vscode

# Set push default behavior
git config --global push.default current

# Enable credential caching
git config --global credential.helper cache

# Cache credentials for 1 hour
git config --global credential.helper 'cache --timeout=3600'

# Set diff tool
git config --global diff.tool vscode

# Enable rerere (Reuse Recorded Resolution)
git config --global rerere.enabled true
```

---

## Repository Basics

### Creating a Repository

```bash
# Initialize a new repository in the current directory
git init

# Initialize a new repository in a specific directory
git init <directory-name>

# Initialize a bare repository (for servers)
git init --bare <repository-name>.git
```

### Cloning a Repository

```bash
# Clone via HTTPS
git clone https://github.com/username/repository.git

# Clone via SSH
git clone git@github.com:username/repository.git

# Clone into a specific directory
git clone https://github.com/username/repository.git my-folder

# Clone a specific branch
git clone -b <branch-name> https://github.com/username/repository.git

# Shallow clone (only latest commit)
git clone --depth 1 https://github.com/username/repository.git

# Clone with submodules
git clone --recurse-submodules https://github.com/username/repository.git
```

### .gitignore File

Create a `.gitignore` file in your repository root to exclude files from tracking:

```gitignore
# Compiled files
*.class
*.o
*.pyc
*.exe

# Directories
node_modules/
dist/
build/
__pycache__/
.venv/

# IDE files
.vscode/
.idea/
*.swp
*.swo

# OS files
.DS_Store
Thumbs.db

# Environment files
.env
.env.local

# Log files
*.log

# Dependency directories
vendor/

# Ignore all .txt files in the root
/*.txt

# But track this specific file
!important.txt

# Ignore all files in any directory named temp
**/temp/
```

### Additional .gitignore Commands

```bash
# Check which rule is ignoring a specific file
git check-ignore -v <file-name>

# List all ignored files
git ls-files --ignored --exclude-standard

# Remove tracked files that should be ignored
git rm --cached <file-name>
git rm -r --cached <directory-name>
```

---

## Staging and Committing

### Checking Status

```bash
# Full status output
git status

# Short/compact status
git status -s
# or
git status --short

# Show branch info in short format
git status -sb
```

**Short status symbols:**

| Symbol | Meaning |
|--------|---------|
| `??` | Untracked |
| `A` | Added to staging |
| `M` | Modified |
| `D` | Deleted |
| `R` | Renamed |
| `C` | Copied |
| `U` | Unmerged |

### Adding Files (Staging)

```bash
# Add a specific file
git add <file-name>

# Add multiple files
git add file1.txt file2.txt file3.txt

# Add all files in current directory
git add .

# Add all files in the entire repository
git add -A
# or
git add --all

# Add all modified and deleted files (not new untracked files)
git add -u

# Add files matching a pattern
git add *.js
git add src/*.py

# Interactive staging
git add -i

# Add changes in patches (partial staging)
git add -p <file-name>
```

### Committing

```bash
# Commit with a message
git commit -m "Your commit message"

# Commit with a title and description
git commit -m "Title" -m "Detailed description"

# Add all tracked modified files and commit (skip staging)
git commit -a -m "Your commit message"
# or
git commit -am "Your commit message"

# Commit with verbose (show diff in editor)
git commit -v

# Amend the last commit (change message or add files)
git commit --amend -m "Updated commit message"

# Amend without changing the commit message
git commit --amend --no-edit

# Create an empty commit
git commit --allow-empty -m "Empty commit"

# Commit with a specific author
git commit --author="Name <email@example.com>" -m "Message"

# Commit with a specific date
git commit --date="2024-01-15T10:30:00" -m "Message"
```

### Removing Files

```bash
# Remove file from working directory and staging area
git rm <file-name>

# Remove file from staging area only (keep in working directory)
git rm --cached <file-name>

# Force remove
git rm -f <file-name>

# Remove directory recursively
git rm -r <directory-name>

# Remove all .log files
git rm --cached *.log
```

### Moving/Renaming Files

```bash
# Rename or move a file
git mv <old-name> <new-name>

# Move file to a different directory
git mv file.txt src/file.txt
```

---

## Branching and Merging

### Branch Basics

```bash
# List local branches
git branch

# List all branches (local + remote)
git branch -a

# List remote branches only
git branch -r

# List branches with last commit
git branch -v

# List branches with last commit and tracking info
git branch -vv

# List merged branches
git branch --merged

# List unmerged branches
git branch --no-merged
```

### Creating Branches

```bash
# Create a new branch
git branch <branch-name>

# Create and switch to a new branch
git checkout -b <branch-name>
# or (Git 2.23+)
git switch -c <branch-name>

# Create a branch from a specific commit
git branch <branch-name> <commit-hash>

# Create a branch from a tag
git branch <branch-name> <tag-name>

# Create a branch that tracks a remote branch
git checkout -b <branch-name> origin/<branch-name>
# or
git switch -c <branch-name> --track origin/<branch-name>
```

### Switching Branches

```bash
# Switch to an existing branch
git checkout <branch-name>
# or (Git 2.23+)
git switch <branch-name>

# Switch to the previous branch
git checkout -
# or
git switch -

# Switch and discard local changes
git checkout -f <branch-name>
```

### Renaming Branches

```bash
# Rename the current branch
git branch -m <new-name>

# Rename a specific branch
git branch -m <old-name> <new-name>

# Rename on remote (delete old, push new)
git push origin --delete <old-name>
git push origin <new-name>
git push origin -u <new-name>
```

### Deleting Branches

```bash
# Delete a local branch (safe - prevents deleting unmerged)
git branch -d <branch-name>

# Force delete a local branch
git branch -D <branch-name>

# Delete a remote branch
git push origin --delete <branch-name>
# or
git push origin :<branch-name>

# Clean up stale remote tracking branches
git fetch --prune
# or
git remote prune origin
```

### Merging

```bash
# Merge a branch into the current branch
git merge <branch-name>

# Merge with a commit message
git merge <branch-name> -m "Merge message"

# Merge without fast-forward (always create merge commit)
git merge --no-ff <branch-name>

# Fast-forward only (fail if not possible)
git merge --ff-only <branch-name>

# Squash merge (combine all commits into one)
git merge --squash <branch-name>
git commit -m "Squashed merge message"

# Abort a merge (if conflicts)
git merge --abort

# Continue merge after resolving conflicts
git merge --continue
```

### Resolving Merge Conflicts

When conflicts occur, Git marks them in the files:

```
<<<<<<< HEAD
Your changes (current branch)
=======
Incoming changes (branch being merged)
>>>>>>> branch-name
```

**Steps to resolve:**

```bash
# 1. Open the conflicting files and edit them
# 2. Remove the conflict markers (<<<<<<<, =======, >>>>>>>)
# 3. Stage the resolved files
git add <resolved-file>

# 4. Complete the merge
git commit

# Or use a merge tool
git mergetool
```

---

## Remote Repositories

### Managing Remotes

```bash
# List remote connections
git remote

# List remotes with URLs
git remote -v

# Add a remote
git remote add <name> <url>
git remote add origin https://github.com/username/repo.git

# Remove a remote
git remote remove <name>
# or
git remote rm <name>

# Rename a remote
git remote rename <old-name> <new-name>

# Change a remote's URL
git remote set-url origin https://github.com/username/new-repo.git

# Show detailed info about a remote
git remote show origin

# Add multiple remotes
git remote add upstream https://github.com/original/repo.git
```

### Fetching

```bash
# Fetch from default remote (origin)
git fetch

# Fetch from a specific remote
git fetch <remote-name>

# Fetch a specific branch
git fetch origin <branch-name>

# Fetch all remotes
git fetch --all

# Fetch and prune deleted remote branches
git fetch --prune
# or
git fetch -p

# Fetch tags
git fetch --tags
```

### Pulling

```bash
# Pull (fetch + merge)
git pull

# Pull from a specific remote and branch
git pull origin main

# Pull with rebase instead of merge
git pull --rebase
# or
git pull -r

# Pull with rebase and autostash
git pull --rebase --autostash

# Pull and allow unrelated histories
git pull origin main --allow-unrelated-histories

# Set default pull behavior
git config --global pull.rebase true   # rebase by default
git config --global pull.ff only       # fast-forward only
```

### Pushing

```bash
# Push to default remote
git push

# Push to a specific remote and branch
git push origin main

# Push and set upstream tracking
git push -u origin main
# or
git push --set-upstream origin main

# Push all branches
git push --all

# Push tags
git push --tags

# Push a specific tag
git push origin <tag-name>

# Force push (⚠️ dangerous - overwrites remote history)
git push --force
# or
git push -f

# Force push with lease (safer - checks for others' changes)
git push --force-with-lease

# Delete a remote branch
git push origin --delete <branch-name>

# Push to multiple remotes
git remote | xargs -L1 git push --all
```

### Tracking Branches

```bash
# Set upstream for current branch
git branch --set-upstream-to=origin/<branch-name>
# or
git branch -u origin/<branch-name>

# Unset upstream
git branch --unset-upstream

# Show tracking branches
git branch -vv
```

---

## Inspecting and Comparing

### Viewing Commit History

```bash
# Show commit log
git log

# Compact one-line format
git log --oneline

# Show last n commits
git log -n 5
# or
git log -5

# Show log with graph
git log --graph

# Show log with graph and branch names
git log --oneline --graph --decorate --all

# Show log with file changes
git log --stat

# Show log with full diff
git log -p
# or
git log --patch

# Show commits by a specific author
git log --author="Name"

# Show commits in a date range
git log --after="2024-01-01" --before="2024-12-31"
git log --since="2 weeks ago"
git log --until="yesterday"

# Search commit messages
git log --grep="keyword"

# Search for changes in code
git log -S "function_name"

# Show commits that changed a specific file
git log -- <file-name>
git log --follow -- <file-name>   # follows renames

# Custom format
git log --pretty=format:"%h - %an, %ar : %s"

# Show merge commits only
git log --merges

# Show non-merge commits only
git log --no-merges

# Show commits between two branches
git log main..feature

# Show commits in feature that are not in main
git log main..feature --oneline
```

**Format placeholders:**

| Placeholder | Description |
|-------------|-------------|
| `%H` | Full commit hash |
| `%h` | Abbreviated commit hash |
| `%an` | Author name |
| `%ae` | Author email |
| `%ar` | Author date (relative) |
| `%ad` | Author date |
| `%s` | Subject (commit message) |
| `%b` | Body |
| `%d` | Ref names (branches, tags) |

### Viewing Changes (Diff)

```bash
# Show unstaged changes
git diff

# Show staged changes
git diff --staged
# or
git diff --cached

# Show all changes (staged + unstaged)
git diff HEAD

# Compare two branches
git diff main..feature
git diff main...feature  # three dots = common ancestor

# Compare two commits
git diff <commit1> <commit2>

# Show changes for a specific file
git diff <file-name>
git diff --staged <file-name>

# Show only file names that changed
git diff --name-only

# Show file names with status
git diff --name-status

# Show statistics
git diff --stat

# Show word-level diff
git diff --word-diff

# Show diff with color words
git diff --color-words

# Compare with a specific commit
git diff HEAD~3

# Ignore whitespace changes
git diff -w
# or
git diff --ignore-all-space
```

### Show Command

```bash
# Show details of the last commit
git show

# Show a specific commit
git show <commit-hash>

# Show a specific file at a specific commit
git show <commit-hash>:<file-path>

# Show a tag
git show <tag-name>

# Show only the commit message
git show --stat

# Show only file names
git show --name-only
```

### Blame

```bash
# Show who changed each line of a file
git blame <file-name>

# Show blame for specific lines
git blame -L 10,20 <file-name>

# Show blame with email
git blame -e <file-name>

# Ignore whitespace changes
git blame -w <file-name>

# Show the commit that last modified each line
git blame --date=short <file-name>
```

### Shortlog

```bash
# Summary of commits by author
git shortlog

# Summary with counts only
git shortlog -s -n

# Summary with email
git shortlog -s -n -e
```

### Reflog

```bash
# Show reference log (all HEAD movements)
git reflog

# Show reflog for a specific branch
git reflog show <branch-name>

# Show reflog with dates
git reflog --date=relative

# Show last n entries
git reflog -n 10
```

---

## Undoing Changes

### Unstaging Files

```bash
# Unstage a specific file
git reset HEAD <file-name>
# or (Git 2.23+)
git restore --staged <file-name>

# Unstage all files
git reset HEAD .
# or
git restore --staged .
```

### Discarding Changes

```bash
# Discard changes in a specific file (working directory)
git checkout -- <file-name>
# or (Git 2.23+)
git restore <file-name>

# Discard all changes in working directory
git checkout -- .
# or
git restore .

# Restore a file from a specific commit
git checkout <commit-hash> -- <file-name>
# or
git restore --source=<commit-hash> <file-name>
```

### Git Reset

```bash
# Soft reset - move HEAD, keep staging and working directory
git reset --soft <commit-hash>

# Mixed reset (default) - move HEAD, reset staging, keep working directory
git reset --mixed <commit-hash>
# or
git reset <commit-hash>

# Hard reset - move HEAD, reset staging AND working directory (⚠️ destructive)
git reset --hard <commit-hash>

# Reset to previous commits
git reset --soft HEAD~1   # Undo last commit, keep changes staged
git reset --mixed HEAD~1  # Undo last commit, unstage changes
git reset --hard HEAD~1   # Undo last commit, discard all changes

# Reset a specific file to a specific commit
git reset <commit-hash> -- <file-name>
```

**Reset Comparison:**

| Type | HEAD | Staging Area | Working Directory |
|------|------|-------------|-------------------|
| `--soft` | ✅ Moved | ❌ Unchanged | ❌ Unchanged |
| `--mixed` | ✅ Moved | ✅ Reset | ❌ Unchanged |
| `--hard` | ✅ Moved | ✅ Reset | ✅ Reset |

### Git Revert

```bash
# Revert a specific commit (creates a new commit)
git revert <commit-hash>

# Revert without auto-committing
git revert --no-commit <commit-hash>
# or
git revert -n <commit-hash>

# Revert a merge commit
git revert -m 1 <merge-commit-hash>

# Revert multiple commits
git revert <oldest-hash>..<newest-hash>

# Abort a revert
git revert --abort

# Continue after resolving conflicts
git revert --continue
```

> **Note:** Use `git revert` for public/shared branches and `git reset` for local changes.

### Recovering Lost Commits

```bash
# Find lost commits using reflog
git reflog

# Restore to a lost commit
git reset --hard <commit-hash-from-reflog>

# Cherry-pick a lost commit
git cherry-pick <commit-hash-from-reflog>

# Create a branch from a lost commit
git branch recovery-branch <commit-hash-from-reflog>
```

### Clean Untracked Files

```bash
# Show what would be removed (dry run)
git clean -n
# or
git clean --dry-run

# Remove untracked files
git clean -f

# Remove untracked files and directories
git clean -fd

# Remove ignored files too
git clean -fX

# Remove everything (untracked + ignored)
git clean -fdx

# Interactive clean
git clean -i
```

---

## Stashing

### Basic Stashing

```bash
# Stash current changes
git stash
# or
git stash push

# Stash with a message
git stash push -m "Work in progress on feature X"
# or
git stash save "Work in progress on feature X"

# Stash including untracked files
git stash -u
# or
git stash --include-untracked

# Stash including ignored files
git stash -a
# or
git stash --all

# Stash specific files
git stash push <file1> <file2>

# Stash with patch (interactive)
git stash -p
```

### Managing Stashes

```bash
# List all stashes
git stash list

# Apply the most recent stash (keep in stash list)
git stash apply

# Apply a specific stash
git stash apply stash@{2}

# Apply and remove from stash list
git stash pop

# Pop a specific stash
git stash pop stash@{2}

# Show stash changes
git stash show

# Show stash diff
git stash show -p
# or
git stash show stash@{0} -p

# Drop a specific stash
git stash drop stash@{0}

# Clear all stashes
git stash clear

# Create a branch from a stash
git stash branch <branch-name>
git stash branch <branch-name> stash@{0}
```

---

## Tagging

### Creating Tags

```bash
# Create a lightweight tag
git tag <tag-name>
git tag v1.0.0

# Create an annotated tag (recommended)
git tag -a <tag-name> -m "Tag message"
git tag -a v1.0.0 -m "Release version 1.0.0"

# Tag a specific commit
git tag -a v1.0.0 <commit-hash> -m "Tag message"

# Create a signed tag (GPG)
git tag -s v1.0.0 -m "Signed release"
```

### Managing Tags

```bash
# List all tags
git tag
# or
git tag -l

# List tags matching a pattern
git tag -l "v1.*"

# Show tag details
git show v1.0.0

# Delete a local tag
git tag -d v1.0.0

# Delete a remote tag
git push origin --delete v1.0.0
# or
git push origin :refs/tags/v1.0.0

# Push a specific tag to remote
git push origin v1.0.0

# Push all tags to remote
git push origin --tags

# Push only annotated tags
git push origin --follow-tags

# Checkout a tag
git checkout v1.0.0

# Create a branch from a tag
git checkout -b <branch-name> v1.0.0
```

---

## Rebasing

### Basic Rebase

```bash
# Rebase current branch onto another branch
git rebase main

# Rebase onto a specific branch
git rebase <base-branch>

# Continue after resolving conflicts
git rebase --continue

# Skip a conflicting commit
git rebase --skip

# Abort the rebase
git rebase --abort
```

### Interactive Rebase

```bash
# Interactive rebase for the last n commits
git rebase -i HEAD~n
git rebase -i HEAD~5

# Interactive rebase onto a branch
git rebase -i main
```

**Interactive rebase commands:**

| Command | Short | Description |
|---------|-------|-------------|
| `pick` | `p` | Use commit as-is |
| `reword` | `r` | Use commit but edit the message |
| `edit` | `e` | Use commit but stop for amending |
| `squash` | `s` | Meld into previous commit (keep message) |
| `fixup` | `f` | Meld into previous commit (discard message) |
| `drop` | `d` | Remove commit |
| `exec` | `x` | Run a shell command |

**Example interactive rebase file:**

```
pick abc1234 First commit
squash def5678 Second commit (will be squashed into first)
reword ghi9012 Third commit (will edit this message)
drop jkl3456 Fourth commit (will be removed)
```

### Rebase vs Merge

| Feature | Rebase | Merge |
|---------|--------|-------|
| History | Linear, clean | Preserves full history |
| Merge commits | No | Yes |
| Conflict resolution | Per-commit | Once |
| Use case | Local branches | Shared branches |
| Safety | ⚠️ Rewrites history | ✅ Safe for shared branches |

> ⚠️ **Golden Rule:** Never rebase commits that have been pushed to a public/shared repository.

---

## Cherry-Picking

```bash
# Apply a specific commit to the current branch
git cherry-pick <commit-hash>

# Cherry-pick without auto-committing
git cherry-pick --no-commit <commit-hash>
# or
git cherry-pick -n <commit-hash>

# Cherry-pick multiple commits
git cherry-pick <hash1> <hash2> <hash3>

# Cherry-pick a range of commits
git cherry-pick <start-hash>..<end-hash>

# Include the start commit
git cherry-pick <start-hash>^..<end-hash>

# Abort cherry-pick
git cherry-pick --abort

# Continue after resolving conflicts
git cherry-pick --continue

# Skip current cherry-pick
git cherry-pick --skip
```

---

## Submodules

```bash
# Add a submodule
git submodule add <repository-url> <path>
git submodule add https://github.com/user/lib.git libs/lib

# Initialize submodules (after cloning)
git submodule init

# Update submodules
git submodule update

# Initialize and update in one command
git submodule update --init

# Recursive initialization (nested submodules)
git submodule update --init --recursive

# Clone with submodules
git clone --recurse-submodules <repository-url>

# Pull changes for all submodules
git submodule foreach git pull origin main

# Check submodule status
git submodule status

# Remove a submodule
git submodule deinit <path>
git rm <path>
rm -rf .git/modules/<path>
```

---

## Git Aliases

### Setting Up Aliases

```bash
# Create aliases
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.unstage 'reset HEAD --'
git config --global alias.last 'log -1 HEAD'
git config --global alias.visual '!gitk'

# Useful aliases
git config --global alias.lg "log --oneline --graph --decorate --all"
git config --global alias.ll "log --pretty=format:'%C(yellow)%h%Creset %s %C(green)(%cr) %C(bold blue)<%an>%Creset %C(red)%d%Creset' --graph"
git config --global alias.amend 'commit --amend --no-edit'
git config --global alias.undo 'reset HEAD~1 --mixed'
git config --global alias.wip 'commit -am "WIP"'
git config --global alias.contributors 'shortlog -s -n'
git config --global alias.today 'log --since=midnight --author="Your Name" --oneline'
```

### Using Aliases

```bash
git st          # instead of git status
git co main     # instead of git checkout main
git br          # instead of git branch
git lg          # pretty log with graph
git amend       # amend last commit
git undo        # undo last commit
```

---

## Advanced Commands

### Bisect (Finding Bugs)

```bash
# Start bisect
git bisect start

# Mark current commit as bad
git bisect bad

# Mark a known good commit
git bisect good <commit-hash>

# Git will checkout a commit in between; test and mark
git bisect good   # if this commit is good
git bisect bad    # if this commit is bad

# Reset/finish bisect
git bisect reset

# Automated bisect with a test script
git bisect run <test-script>
git bisect run npm test
```

### Worktrees

```bash
# Add a new worktree
git worktree add <path> <branch>
git worktree add ../project-feature feature-branch

# List worktrees
git worktree list

# Remove a worktree
git worktree remove <path>

# Prune stale worktree entries
git worktree prune
```

### Archive

```bash
# Create a tar archive of the latest commit
git archive --format=tar HEAD > archive.tar

# Create a zip archive
git archive --format=zip HEAD > archive.zip

# Archive a specific branch
git archive --format=zip main > main.zip

# Archive with a prefix directory
git archive --format=tar --prefix=project/ HEAD > project.tar
```

### Bundle

```bash
# Create a bundle of the entire repo
git bundle create repo.bundle --all

# Create a bundle of a specific branch
git bundle create repo.bundle main

# Clone from a bundle
git clone repo.bundle

# Verify a bundle
git bundle verify repo.bundle
```

### Grep (Search Code)

```bash
# Search for a pattern in tracked files
git grep "search_term"

# Search with line numbers
git grep -n "search_term"

# Search with count
git grep -c "search_term"

# Search in a specific commit
git grep "search_term" <commit-hash>

# Search with context
git grep -p "search_term"

# Case-insensitive search
git grep -i "search_term"
```

### Filter-Branch / Filter-Repo

```bash
# Remove a file from entire history (using git-filter-repo - recommended)
git filter-repo --path <file-to-remove> --invert-paths

# Change author email in entire history
git filter-repo --email-callback '
    return email.replace(b"old@email.com", b"new@email.com")
'

# Legacy: filter-branch (not recommended for new usage)
git filter-branch --tree-filter 'rm -f password.txt' HEAD
```

### Other Useful Commands

```bash
# Count commits
git rev-list --count HEAD
git rev-list --count main

# Show the root commit
git rev-list --max-parents=0 HEAD

# Find the common ancestor of two branches
git merge-base main feature

# Verify objects
git fsck

# Garbage collection
git gc
git gc --aggressive

# Show object type
git cat-file -t <hash>

# Show object content
git cat-file -p <hash>

# List all tracked files
git ls-files

# List tree objects
git ls-tree HEAD
git ls-tree -r HEAD --name-only
```

---

## Git Best Practices

### Commit Message Convention

Follow the **Conventional Commits** format:

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Types:**

| Type | Description |
|------|-------------|
| `feat` | A new feature |
| `fix` | A bug fix |
| `docs` | Documentation changes |
| `style` | Formatting, missing semicolons, etc. |
| `refactor` | Code restructuring without changing behavior |
| `perf` | Performance improvements |
| `test` | Adding or modifying tests |
| `chore` | Maintenance tasks |
| `ci` | CI/CD changes |
| `build` | Build system changes |
| `revert` | Reverting a previous commit |

**Examples:**

```
feat(auth): add login functionality

fix(api): resolve null pointer in user endpoint

docs(readme): update installation instructions

refactor(core): simplify database connection logic

chore(deps): update dependency versions
```

### General Best Practices

- ✅ **Commit often** — make small, focused commits
- ✅ **Write clear commit messages** — explain *why*, not just *what*
- ✅ **Use branches** — one branch per feature or fix
- ✅ **Pull before push** — always sync before pushing
- ✅ **Don't commit generated files** — use `.gitignore`
- ✅ **Review changes before committing** — use `git diff` and `git status`
- ✅ **Never force push to shared branches** — unless absolutely necessary
- ✅ **Use `.gitignore` from the start** — avoid committing secrets or binaries
- ✅ **Tag releases** — use semantic versioning (v1.0.0)
- ✅ **Keep branches up to date** — regularly merge or rebase from main

---

## Git Workflow Models

### 1. Feature Branch Workflow

```
main ─────────────────────────────────
        \                    /
         feature-branch ────
```

```bash
git checkout main
git pull
git checkout -b feature/new-feature
# ... make changes ...
git add .
git commit -m "feat: implement new feature"
git push -u origin feature/new-feature
# Create Pull Request
# After review, merge to main
```

### 2. Gitflow Workflow

```
main ───────────────────────────────── (production)
  │                        ▲
  └── develop ─────────────┤────────── (integration)
        │           ▲      │
        └── feature ┘      │
                     release ──────── (staging)
                           hotfix ─── (urgent fixes)
```

**Branches:**

| Branch | Purpose |
|--------|---------|
| `main` | Production-ready code |
| `develop` | Integration branch |
| `feature/*` | New features |
| `release/*` | Release preparation |
| `hotfix/*` | Urgent production fixes |

### 3. Trunk-Based Development

```
main ─────────────────────────────────
   \   /  \   /  \   /
    ──      ──      ──     (short-lived branches)
```

- All developers commit to a single branch (main/trunk)
- Short-lived feature branches (1-2 days max)
- Feature flags for incomplete features
- Continuous integration

### 4. Forking Workflow

```bash
# 1. Fork the repository on GitHub
# 2. Clone your fork
git clone https://github.com/your-username/repo.git

# 3. Add upstream remote
git remote add upstream https://github.com/original/repo.git

# 4. Create a feature branch
git checkout -b feature/my-feature

# 5. Make changes and commit
git add .
git commit -m "feat: add my feature"

# 6. Push to your fork
git push origin feature/my-feature

# 7. Create a Pull Request to the original repository

# 8. Keep your fork updated
git fetch upstream
git checkout main
git merge upstream/main
git push origin main
```

---

## Cheat Sheet

### Quick Reference Table

| Command | Description |
|---------|-------------|
| `git init` | Initialize a new repository |
| `git clone <url>` | Clone a repository |
| `git status` | Check status |
| `git add .` | Stage all changes |
| `git commit -m "msg"` | Commit changes |
| `git push` | Push to remote |
| `git pull` | Pull from remote |
| `git fetch` | Fetch without merging |
| `git branch` | List branches |
| `git branch <name>` | Create a branch |
| `git checkout <name>` | Switch branch |
| `git switch <name>` | Switch branch (new) |
| `git merge <name>` | Merge a branch |
| `git rebase <name>` | Rebase onto branch |
| `git log --oneline` | View compact log |
| `git diff` | View changes |
| `git stash` | Stash changes |
| `git stash pop` | Apply and remove stash |
| `git tag <name>` | Create a tag |
| `git reset --hard HEAD~1` | Undo last commit (destructive) |
| `git revert <hash>` | Revert a commit (safe) |
| `git cherry-pick <hash>` | Apply a specific commit |
| `git remote -v` | View remotes |
| `git blame <file>` | See who changed each line |
| `git bisect start` | Start binary search for bugs |
| `git clean -fd` | Remove untracked files/dirs |

### Common Workflows

```bash
# 📥 Starting a new project
git init
git add .
git commit -m "Initial commit"
git remote add origin <url>
git push -u origin main

# 🔄 Daily workflow
git pull
# ... make changes ...
git add .
git commit -m "description of changes"
git push

# 🌿 Feature branch workflow
git checkout -b feature/awesome-feature
# ... make changes ...
git add .
git commit -m "feat: add awesome feature"
git push -u origin feature/awesome-feature
# Create PR → Review → Merge

# 🔥 Hotfix workflow
git checkout main
git pull
git checkout -b hotfix/critical-bug
# ... fix the bug ...
git commit -am "fix: resolve critical bug"
git push -u origin hotfix/critical-bug
# Create PR → Merge → Deploy

# 🔙 Undo mistakes
git reset --soft HEAD~1      # Undo commit, keep changes staged
git reset --mixed HEAD~1     # Undo commit, unstage changes
git reset --hard HEAD~1      # Undo commit, discard everything
git revert <hash>            # Create a new "undo" commit
```

---

## 📚 Additional Resources

| Resource | Link |
|----------|------|
| Official Git Documentation | [git-scm.com/doc](https://git-scm.com/doc) |
| Pro Git Book (Free) | [git-scm.com/book](https://git-scm.com/book) |
| GitHub Learning Lab | [lab.github.com](https://lab.github.com) |
| Interactive Git Branching | [learngitbranching.js.org](https://learngitbranching.js.org) |
| Git Flight Rules | [github.com/k88hudson/git-flight-rules](https://github.com/k88hudson/git-flight-rules) |
| Conventional Commits | [conventionalcommits.org](https://www.conventionalcommits.org) |

---

> 💡 **Tip:** Practice regularly and don't be afraid to experiment. Git's reflog almost always allows you to recover from mistakes!

---

*⭐ If you found this guide helpful, consider bookmarking it for future reference!*
