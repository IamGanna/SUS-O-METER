# AGENTS.md

Rules for any AI agent working in this repository. Follow all of them.

## 1. Plan first, then code

- Do not start coding right away. No "vibe coding".
- Before you change any code, write a short plan:
  - What you will change.
  - Which files you will touch.
  - Why this approach works.
- Wait for my approval before you write code.
- If the plan needs to change while you work, stop and tell me first.

## 2. Git: never commit or push

- Do not run `git commit`.
- Do not run `git push`.
- Do not create, merge, rebase, or delete branches.
- Do not change git history or git config.
- You may read git state (`git status`, `git diff`, `git log`) to understand the code.
- I will review the changes and commit them myself.

## 3. Communication

- Do not use emoji.
- Use short, simple sentences. Write so a beginner can follow.
- Explain technical terms the first time you use them.
- Say what you did and why, in plain words.
- If something is unclear, ask me instead of guessing.
- If you are not sure something works, say so.

## 4. Keep it simple

- Do not overengineer. Write the simplest code that solves the problem.
- Do not add abstractions, layers, or config options that are not needed now.
- Do not leave dead code: no unused functions, variables, imports, or commented-out code.
- Only change what the task needs. Do not refactor unrelated code.

## 5. Dependencies

- Do not add any new dependency (library, package, tool) without asking me first.
- When you ask, explain:
  - What the dependency is.
  - Why it is needed.
  - Whether we can do it without it.
- Prefer the standard library and code that already exists in the project.