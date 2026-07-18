# SDET Interview & Role Prep Guide
### (Playwright + JavaScript | Compliance/Investigation Product | MERN + C++ background, no formal QA experience)

> Scope note: This guide **skips DSA** as requested (you already have notes for that). It focuses on everything else in the JD: testing fundamentals, Playwright/JavaScript, API testing, Git workflows, CI/CD, SQL for validation, bug triage, and interview prep.
>
> Note on TypeScript: the JD lists TypeScript, and most real-world Playwright codebases use it. Since you already know JS, everything here uses plain JavaScript so you can start immediately — but Section 4 has a short "if a team uses TypeScript" primer, since you'll likely see `.ts` files in interviews or on the job and should be able to read them even if you write JS.

---

## Table of Contents

1. [How to Use This Guide](#1-how-to-use-this-guide)
2. [Software Testing Fundamentals](#2-software-testing-fundamentals)
3. [Test Case Design Techniques](#3-test-case-design-techniques)
4. [JavaScript Patterns for Testers (+ Reading TypeScript)](#4-javascript-patterns-for-testers--reading-typescript)
5. [Playwright Deep Dive](#5-playwright-deep-dive)
6. [Page Object Model & Test Frameworks](#6-page-object-model--test-frameworks)
7. [API Testing](#7-api-testing)
8. [Git & Collaborative Workflows](#8-git--collaborative-workflows)
9. [CI/CD with GitHub Actions](#9-cicd-with-github-actions)
10. [SQL for Data Validation](#10-sql-for-data-validation)
11. [Bug Reporting, Triage & Bug Life Cycle](#11-bug-reporting-triage--bug-life-cycle)
12. [AI-Assisted Testing (Copilot/Claude)](#12-ai-assisted-testing-copilotclaude)
13. [Portfolio Project Ideas](#13-portfolio-project-ideas)
14. [Interview Question Bank](#14-interview-question-bank)
15. [30-60-90 Day Study Plan](#15-30-60-90-day-study-plan)
16. [Quick Reference Cheat Sheet](#16-quick-reference-cheat-sheet)

---

## 1. How to Use This Guide

- Copy this file into a GitHub repo (e.g., `sdet-prep-notes`) as `README.md` — it's designed to render well there.
- Work through sections **in order** the first time; after that, use it as a reference.
- Every code-heavy section has runnable snippets. Actually type them out — don't just read. Muscle memory matters for a coding assessment.
- Since you know MERN (JS/Node/React) and C++ OOP, you already have ~70% of the programming foundation. This guide leans on that and fills the **testing-specific** 30%.

---

## 2. Software Testing Fundamentals

### 2.1 Why Testing Exists (mental model)

As a developer you think: *"Does this work?"*
As a tester you think: *"How can I make this break, and does it break in ways that matter?"*

This is the single biggest mindset shift. You're not verifying the happy path only — you're actively hunting for the code's blind spots.

### 2.2 Levels of Testing

| Level | What it checks | Who writes it | Speed |
|---|---|---|---|
| **Unit** | A single function/class in isolation | Developers | Milliseconds |
| **Integration** | Multiple units/modules working together (e.g., API + DB) | Developers/SDETs | Seconds |
| **End-to-End (E2E)** | Full user journey through UI, hitting real/staged backend | SDETs | Seconds–minutes |
| **System** | Entire application as a whole, in a production-like environment | QA | Minutes |
| **Acceptance (UAT)** | Does it meet business requirements? | QA/Product | Varies |

Your role (SDET) lives mostly at **Integration + E2E + API**, using Playwright for E2E/UI and API testing.

### 2.3 Types of Testing (by purpose, not level)

- **Functional testing** — does the feature do what it's supposed to do? (e.g., "Clicking Submit creates a new investigation case.")
- **Regression testing** — did a new change break something that used to work? This is what most of your *automated* suite exists for.
- **Smoke testing** — a fast, shallow "is the build even alive?" check (login works, homepage loads, core nav works) run before deeper testing.
- **Sanity testing** — a narrow, deeper check after a specific bug fix, confirming that fix works without doing a full regression pass.
- **Exploratory testing** — unscripted, manual, creative testing to find issues scripted tests miss.
- **Negative testing** — deliberately feeding invalid/unexpected input (empty fields, huge strings, wrong file types, SQL-injection-like strings) to see if the system fails gracefully.
- **Boundary testing** — testing at the edges of valid ranges (see Section 3).
- **Cross-browser / cross-device testing** — same feature, different browsers (Chromium, Firefox, WebKit) — Playwright is built for this.
- **Performance/load testing** — not your core job here, but you should know it's a different discipline (tools: k6, JMeter).
- **Security testing** — especially relevant since this is a **compliance/investigation product** — expect sensitivity around access control, audit trails, data leakage between roles/tenants.

### 2.4 Manual vs Automated Testing

- Automate: repetitive regression flows, things run every build, things too tedious/error-prone for humans (checking 50 rows of a table).
- Keep manual: exploratory testing, first-time testing of a brand-new feature (UI is still shifting), one-off visual/UX judgment calls.
- Rule of thumb interviewers like: **"Automate what regresses; explore what's new."**

### 2.5 The Testing Pyramid

```
        /\
       /E2E\        <- few, slow, expensive, high confidence
      /------\
     / Integ. \     <- more, medium speed
    /----------\
   /   Unit     \   <- many, fast, cheap
  /--------------\
```

As an SDET you mostly live in the **top third**, but you should know that a healthy suite doesn't put everything in E2E — that's slow and flaky. If someone asks "why not just write everything as E2E tests?", the answer is: **speed, flakiness, and cost of maintenance**.

### 2.6 Flakiness — a core SDET concept

A "flaky" test passes and fails intermittently with no code change. Common causes:
- Race conditions / not waiting properly for async UI updates
- Hardcoded `sleep()` instead of proper waits
- Shared test data / test order dependency
- Environment instability (network, test DB state)

Interviewers **love** asking "how do you handle flaky tests?" — have a real answer (see Section 5.7).

---

## 3. Test Case Design Techniques

These are classic QA techniques — expect at least one interview question here.

### 3.1 Equivalence Partitioning (EP)

Split inputs into groups ("partitions") where all values in a group should behave the same way. Test **one representative** from each partition instead of every value.

Example: An age field that must be 18–65.
- Partition 1: < 18 (invalid)
- Partition 2: 18–65 (valid)
- Partition 3: > 65 (invalid)

### 3.2 Boundary Value Analysis (BVA)

Bugs love boundaries (`<` vs `<=` mistakes). Test the edges:
For age 18–65 → test **17, 18, 19, 64, 65, 66**.

### 3.3 Decision Table Testing

Used when output depends on a **combination** of conditions.

| Logged in? | Has permission? | Case status | Expected result |
|---|---|---|---|
| No | - | - | Redirect to login |
| Yes | No | - | 403 Forbidden |
| Yes | Yes | Closed | Read-only view |
| Yes | Yes | Open | Editable view |

### 3.4 State Transition Testing

Useful for a compliance/investigation product — cases likely move through states: `Draft → Submitted → Under Review → Approved/Rejected → Closed`. Test:
- Valid transitions (Draft → Submitted)
- Invalid transitions (Closed → Draft, should be blocked)
- Side effects of each transition (e.g., does an audit log entry get created?)

### 3.5 Error Guessing

Based on experience/intuition — e.g., try special characters in name fields, upload a 0-byte file, submit a form twice quickly (double-submit bug), test with an expired session token.

### 3.6 Writing a Good Test Case (format)

```
Test Case ID: TC_CASE_001
Title: Verify investigator can add evidence to an open case
Preconditions: User logged in as "Investigator" role; a case exists with status = Open
Steps:
  1. Navigate to Case Details page
  2. Click "Add Evidence"
  3. Upload a valid PDF file
  4. Click "Save"
Expected Result: Evidence appears in the case timeline with correct filename, uploader, and timestamp
Priority: High
```

---

## 4. JavaScript Patterns for Testers (+ Reading TypeScript)

You already know JS from MERN, so this section is short — just the patterns Playwright leans on heavily, plus enough TypeScript literacy to read a `.ts` test file if your team (or an interviewer) hands you one.

### 4.1 async/await — the pattern you'll use in almost every line

```javascript
async function openCase(page, caseId) {
  const response = await page.request.get(`/api/cases/${caseId}`);
  const data = await response.json();
  return data;
}
```
Playwright is **async-first** — every action (`click`, `fill`, `waitFor...`) returns a Promise. Forgetting `await` is the #1 beginner bug: the test moves on before the action actually finishes, causing flaky or failing tests, and Playwright's linter will usually warn you about it.

### 4.2 Destructuring — Playwright's test function relies on this constantly

```javascript
const { test, expect } = require('@playwright/test');
// or, in an ESM project:
import { test, expect } from '@playwright/test';

test('example', async ({ page, request }) => {
  // "page" and "request" are destructured out of Playwright's fixture object
});
```
If you've used React props destructuring, this is the exact same idea — Playwright just hands you an object of built-in "fixtures" (`page`, `request`, `context`, `browser`, etc.) and you pull out only what you need.

### 4.3 JSDoc — optional lightweight typing without switching to TypeScript

You can get IDE autocomplete and some type-checking in plain `.js` files using comments — useful for documenting your own utilities without adopting full TypeScript:

```javascript
/**
 * @param {import('@playwright/test').Page} page
 * @param {string} username
 * @param {string} password
 */
async function login(page, username, password) {
  await page.getByLabel('Username').fill(username);
  await page.getByLabel('Password').fill(password);
  await page.getByRole('button', { name: 'Log in' }).click();
}
```

### 4.4 Reading TypeScript (you don't need to write it, but you should be able to read it)

Many real Playwright codebases — and a lot of official docs/examples — use `.ts` files. The good news: it's JS plus a thin layer of type annotations that you can mentally strip out. Side-by-side:

```typescript
// TypeScript
function login(username: string, password: string): Promise<void> { ... }

interface User {
  username: string;
  role: "admin" | "investigator" | "viewer";
}
```

```javascript
// The equivalent plain JavaScript — same logic, just no annotations
function login(username, password) { ... }

// "interface" has no JS equivalent — it's a compile-time-only shape description.
// In JS you'd just document the shape with a comment or JSDoc, e.g.:
// { username: string, role: 'admin' | 'investigator' | 'viewer' }
```

**Rule of thumb for reading `.ts` code:** ignore anything after a `:` on a parameter/variable, ignore `interface`/`type` blocks (they just describe shapes, they don't run), and ignore `<T>` generics — they're just placeholders for "some type." The logic underneath is identical to JS.

If a team specifically requires you to write TypeScript, the jump from here is small: mostly adding `: string`, `: number` etc. after variables/params, and using `interface`/`type` to describe object shapes. Don't let it block you from applying — it's a day-or-two ramp-up, not a different language.

---

## 5. Playwright Deep Dive

### 5.1 Why Playwright (know this for interviews)

- Auto-waiting: it waits for elements to be actionable before interacting — fewer manual `sleep()` calls than Selenium.
- One API, three browser engines: Chromium, Firefox, WebKit.
- Built-in test runner (`@playwright/test`) — no need for separate Mocha/Jasmine glue like older Selenium setups.
- Network interception/mocking built in.
- Auto-generated traces, screenshots, videos on failure.
- Parallel execution out of the box.

### 5.2 Installation

```bash
npm init playwright@latest
# Choose: JavaScript, tests folder, GitHub Actions workflow: yes
npx playwright install        # installs browser binaries
```

Project structure it creates:
```
playwright.config.js
tests/
  example.spec.js
package.json
```

### 5.3 Your First Test

```javascript
const { test, expect } = require('@playwright/test');

test('user can log in with valid credentials', async ({ page }) => {
  await page.goto('https://app.example.com/login');
  await page.fill('#username', 'investigator1');
  await page.fill('#password', 'SecurePass123!');
  await page.click('button[type="submit"]');

  await expect(page).toHaveURL(/.*dashboard/);
  await expect(page.locator('h1')).toHaveText('Dashboard');
});
```

Run it:
```bash
npx playwright test
npx playwright test --headed        # see the browser
npx playwright test --debug         # step through
npx playwright show-report          # open HTML report
```

### 5.4 Locators (the most important skill)

Playwright recommends **user-facing locators** over brittle CSS/XPath where possible.

```javascript
// Preferred — resilient to markup changes
page.getByRole('button', { name: 'Submit' });
page.getByLabel('Username');
page.getByPlaceholder('Search cases...');
page.getByText('Case #1024');
page.getByTestId('case-status-badge');   // needs data-testid in the app

// CSS / XPath — use when nothing else works
page.locator('.case-table tr:nth-child(2)');
page.locator('xpath=//button[text()="Save"]');
```

**Best practice**: ask the frontend devs to add `data-testid` attributes to key elements. This is a real conversation you'll have on the job — mention it in interviews, it shows maturity.

### 5.5 Common Actions

```javascript
await page.goto(url);
await page.click(selector);
await page.fill(selector, 'text');       // clears then types
await page.type(selector, 'text');       // types char by char (rarely needed)
await page.check(selector);              // checkbox/radio
await page.selectOption(selector, 'value');
await page.hover(selector);
await page.press(selector, 'Enter');
await page.locator(selector).setInputFiles('path/to/file.pdf'); // file upload
```

### 5.6 Assertions

```javascript
const { expect } = require('@playwright/test');

await expect(page.locator('h1')).toHaveText('Dashboard');
await expect(page.locator('.error')).toBeVisible();
await expect(page.locator('#submit')).toBeDisabled();
await expect(page).toHaveURL('https://app.example.com/dashboard');
await expect(page).toHaveTitle(/Compliance Portal/);
expect(responseBody.status).toBe('SUBMITTED');   // plain value assertion
```

Playwright's `expect` **auto-retries** until timeout — this is why you rarely need manual waits for assertions.

### 5.7 Waiting Strategy (flakiness prevention — big interview topic)

```javascript
// GOOD — Playwright auto-waits for actionability before clicking
await page.click('#submit');

// GOOD — explicit wait for a condition
await page.waitForSelector('.case-loaded');
await page.waitForResponse(resp => resp.url().includes('/api/cases') && resp.status() === 200);
await page.waitForLoadState('networkidle');

// BAD — never do this in real projects
await page.waitForTimeout(5000);   // arbitrary sleep — causes flakiness & slowness
```

**Interview line to remember:** *"I avoid hardcoded waits and instead wait for specific conditions — a network response, a DOM state, or an element becoming visible — because arbitrary sleeps make tests both slow and unreliable."*

### 5.8 Hooks & Fixtures

```javascript
const { test, expect } = require('@playwright/test');

test.beforeEach(async ({ page }) => {
  await page.goto('https://app.example.com/login');
  await page.fill('#username', 'investigator1');
  await page.fill('#password', 'SecurePass123!');
  await page.click('button[type="submit"]');
});

test.afterEach(async ({ page }, testInfo) => {
  if (testInfo.status !== testInfo.expectedStatus) {
    await page.screenshot({ path: `failures/${testInfo.title}.png` });
  }
});
```

Custom fixtures (reusable setup, e.g., a logged-in page) — a step up you'll likely encounter in a real framework:

```javascript
// fixtures.js
const base = require('@playwright/test');

exports.test = base.test.extend({
  authenticatedPage: async ({ page }, use) => {
    await page.goto('/login');
    await page.fill('#username', 'investigator1');
    await page.fill('#password', 'pass');
    await page.click('button[type=submit]');
    await use(page);   // hand off to the test
  },
});
exports.expect = base.expect;
```

```javascript
// case.spec.js
const { test, expect } = require('./fixtures');

test('open case detail', async ({ authenticatedPage: page }) => {
  await page.goto('/cases/1024');
  await expect(page.locator('h1')).toContainText('Case #1024');
});
```

### 5.9 Configuration essentials (`playwright.config.js`)

```javascript
const { defineConfig, devices } = require('@playwright/test');

module.exports = defineConfig({
  testDir: './tests',
  timeout: 30_000,
  retries: process.env.CI ? 2 : 0,   // retry flaky tests in CI only
  workers: process.env.CI ? 4 : undefined,
  reporter: [['html'], ['list']],
  use: {
    baseURL: 'https://staging.app.example.com',
    trace: 'on-first-retry',
    screenshot: 'only-on-failure',
    video: 'retain-on-failure',
  },
  projects: [
    { name: 'chromium', use: { ...devices['Desktop Chrome'] } },
    { name: 'firefox', use: { ...devices['Desktop Firefox'] } },
    { name: 'webkit', use: { ...devices['Desktop Safari'] } },
  ],
});
```

### 5.10 Debugging Tools

- `npx playwright test --debug` — opens Playwright Inspector, step through actions.
- `npx playwright codegen https://app.example.com` — records your clicks and generates code (great for learning locators quickly, but don't ship raw codegen output — refactor into POM).
- **Trace Viewer**: `npx playwright show-trace trace.zip` — timeline, DOM snapshots, network, console logs for a failed test. This is the single best debugging tool in Playwright — know it cold for interviews.

### 5.11 Network Interception / Mocking

```javascript
// Mock an API response to test UI behavior in isolation
await page.route('**/api/cases/1024', route => {
  route.fulfill({
    status: 200,
    contentType: 'application/json',
    body: JSON.stringify({ id: 1024, status: 'CLOSED' }),
  });
});

// Simulate a server error to test error-handling UI
await page.route('**/api/cases/1024', route => route.fulfill({ status: 500 }));
```

Useful for testing edge cases (server errors, slow responses, empty states) without needing the backend to actually produce them.

---

## 6. Page Object Model & Test Frameworks

### 6.1 Why POM

Without it, your tests are full of duplicated selectors — one UI change breaks 40 test files. POM centralizes locators/actions for a page into one class; tests read like plain English.

### 6.2 Example POM

```javascript
// pages/LoginPage.js

class LoginPage {
  /** @param {import('@playwright/test').Page} page */
  constructor(page) {
    this.page = page;
    this.usernameInput = page.getByLabel('Username');
    this.passwordInput = page.getByLabel('Password');
    this.submitButton = page.getByRole('button', { name: 'Log in' });
    this.errorMessage = page.locator('.error-message');
  }

  async goto() {
    await this.page.goto('/login');
  }

  async login(username, password) {
    await this.usernameInput.fill(username);
    await this.passwordInput.fill(password);
    await this.submitButton.click();
  }
}

module.exports = { LoginPage };
```

```javascript
// pages/CaseDetailsPage.js

class CaseDetailsPage {
  /** @param {import('@playwright/test').Page} page */
  constructor(page) {
    this.page = page;
    this.title = page.locator('h1');
    this.addEvidenceButton = page.getByRole('button', { name: 'Add Evidence' });
    this.evidenceList = page.locator('.evidence-item');
  }

  async goto(caseId) {
    await this.page.goto(`/cases/${caseId}`);
  }

  async addEvidence(filePath) {
    await this.addEvidenceButton.click();
    await this.page.locator('input[type=file]').setInputFiles(filePath);
    await this.page.getByRole('button', { name: 'Save' }).click();
  }
}

module.exports = { CaseDetailsPage };
```

```javascript
// tests/case-evidence.spec.js
const { test, expect } = require('@playwright/test');
const { LoginPage } = require('../pages/LoginPage');
const { CaseDetailsPage } = require('../pages/CaseDetailsPage');

test('investigator can add evidence to an open case', async ({ page }) => {
  const loginPage = new LoginPage(page);
  const casePage = new CaseDetailsPage(page);

  await loginPage.goto();
  await loginPage.login('investigator1', 'SecurePass123!');

  await casePage.goto(1024);
  await casePage.addEvidence('test-data/sample-evidence.pdf');

  await expect(casePage.evidenceList).toHaveCount(1);
});
```

Notice the test itself now reads almost like plain English — that readability is the whole point of POM, and it's exactly what interviewers look for in a code sample.

### 6.3 Reusable Utilities

Beyond POM, real frameworks have a `utils/` folder for shared logic:

```javascript
// utils/apiHelper.js — set up test data via API instead of clicking through UI (faster)

/**
 * @param {import('@playwright/test').APIRequestContext} request
 * @param {string} status
 */
async function createTestCase(request, status = 'OPEN') {
  const response = await request.post('/api/cases', {
    data: { title: 'Automated Test Case', status },
  });
  return response.json();
}

module.exports = { createTestCase };
```

```javascript
// utils/testData.js
const users = {
  investigator: { username: 'investigator1', password: 'SecurePass123!' },
  admin: { username: 'admin1', password: 'AdminPass123!' },
};

module.exports = { users };
```

**Interview-relevant principle:** Use the **API** to set up test preconditions (e.g., "a case must already exist") rather than clicking through the UI every time. UI-driven setup is slow and adds unrelated points of failure to a test that's actually about something else.

---

## 7. API Testing

Since the JD explicitly calls out API testing, expect this in the assessment and interview.

### 7.1 REST Basics Refresher

| Method | Purpose | Idempotent? |
|---|---|---|
| GET | Read a resource | Yes |
| POST | Create a resource | No |
| PUT | Replace a resource fully | Yes |
| PATCH | Partially update a resource | No (usually) |
| DELETE | Remove a resource | Yes |

Common status codes to know cold:
- `200` OK, `201` Created, `204` No Content
- `400` Bad Request, `401` Unauthorized, `403` Forbidden, `404` Not Found, `409` Conflict
- `500` Internal Server Error, `503` Service Unavailable

### 7.2 API Testing with Playwright's `request` fixture

Playwright can test APIs directly — no browser needed, much faster than E2E.

```javascript
const { test, expect } = require('@playwright/test');

test('GET /api/cases/1024 returns correct case data', async ({ request }) => {
  const response = await request.get('/api/cases/1024');

  expect(response.status()).toBe(200);
  const body = await response.json();
  expect(body).toMatchObject({
    id: 1024,
    status: expect.stringMatching(/OPEN|CLOSED|SUBMITTED/),
  });
});

test('POST /api/cases creates a new case', async ({ request }) => {
  const response = await request.post('/api/cases', {
    data: { title: 'New Investigation', priority: 'High' },
  });
  expect(response.status()).toBe(201);
  const body = await response.json();
  expect(body.id).toBeDefined();
  expect(body.title).toBe('New Investigation');
});

test('unauthorized user gets 401 on protected endpoint', async ({ request }) => {
  const response = await request.get('/api/admin/users', {
    headers: { Authorization: '' },
  });
  expect(response.status()).toBe(401);
});
```

### 7.3 Things to Check in an API Test (beyond just status code)

- Status code correctness
- Response body schema (right fields, right types)
- Response time (basic performance sanity)
- Headers (e.g., `Content-Type: application/json`)
- Error response structure on failure paths
- Auth/permission enforcement (critical for a compliance product — role X should NOT see role Y's cases)
- Pagination, filtering, sorting params behave correctly
- Idempotency where expected (calling DELETE twice shouldn't error weirdly)

### 7.4 Combining API + UI in one test (very realistic scenario)

```javascript
test('newly created case (via API) appears in UI case list', async ({ page, request }) => {
  // Fast setup via API
  const res = await request.post('/api/cases', { data: { title: 'API Seeded Case' } });
  const created = await res.json();

  // Verify via UI
  await page.goto('/login');
  // ... login steps
  await page.goto('/cases');
  await expect(page.getByText('API Seeded Case')).toBeVisible();
});
```

### 7.5 Postman (good to know even though Playwright can do this)

- Collections, environments, variables (`{{baseUrl}}`)
- Pre-request scripts & test scripts (JS-based assertions, same mental model as Playwright's `expect`)
- Newman — CLI runner for Postman collections, used in CI
- Know this exists and roughly how it works; you don't need to master it if Playwright is the team's stack.

---

## 8. Git & Collaborative Workflows

You've used Git for MERN projects — here's the SDET-flavored layer.

### 8.1 Core commands you must be fluent in

```bash
git clone <repo>
git checkout -b feature/add-case-evidence-tests
git status
git add tests/case-evidence.spec.js
git commit -m "test: add evidence upload coverage for open cases"
git push origin feature/add-case-evidence-tests
git pull --rebase origin main
```

### 8.2 Branching model you'll likely encounter

- `main`/`master` — always deployable
- `develop` (sometimes) — integration branch
- `feature/*`, `bugfix/*`, `test/*` — short-lived branches per ticket
- Pull Request (PR) → code review → merge (often squash merge)

### 8.3 Good PR hygiene for test code (mention in interview — shows maturity)

- Small, focused PRs (one feature's tests per PR, not a giant dump)
- Descriptive commit messages: `test: cover negative login scenarios` not `updates`
- Don't commit `node_modules`, `.env`, test artifacts (`playwright-report/`, `test-results/`) — use `.gitignore`
- Resolve merge conflicts in test files carefully — two people adding tests to the same file is common

### 8.4 Sample `.gitignore` for a Playwright project

```
node_modules/
playwright-report/
test-results/
.env
*.log
```

---

## 9. CI/CD with GitHub Actions

### 9.1 Why this matters for the role

"Integrate automated tests into CI/CD pipelines" is a direct JD line. Expect this in interviews and possibly the assessment.

### 9.2 Basic GitHub Actions Workflow for Playwright

```yaml
# .github/workflows/playwright.yml
name: Playwright Tests

on:
  push:
    branches: [main]
  pull_request:
    branches: [main]

jobs:
  test:
    timeout-minutes: 30
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4

      - uses: actions/setup-node@v4
        with:
          node-version: 20

      - name: Install dependencies
        run: npm ci

      - name: Install Playwright Browsers
        run: npx playwright install --with-deps

      - name: Run Playwright tests
        run: npx playwright test

      - uses: actions/upload-artifact@v4
        if: always()
        with:
          name: playwright-report
          path: playwright-report/
          retention-days: 14
```

### 9.3 Concepts to be able to explain

- **CI (Continuous Integration)**: every push/PR automatically triggers build + test, catching regressions early.
- **CD (Continuous Deployment/Delivery)**: automatically deploying code that passes tests (Delivery = manual approval gate before prod; Deployment = fully automatic).
- **Why run tests in CI and not just locally?** Consistency (same environment every time), catches "works on my machine" issues, gatekeeps merges, gives the whole team visibility.
- **Parallelization in CI**: Playwright's `workers` config + GitHub Actions matrix strategy can shard tests across multiple runners for speed:

```yaml
strategy:
  matrix:
    shardIndex: [1, 2, 3, 4]
    shardTotal: [4]
steps:
  - run: npx playwright test --shard=${{ matrix.shardIndex }}/${{ matrix.shardTotal }}
```

- **Handling flaky tests in CI**: `retries` config (Section 5.9), quarantining known-flaky tests with `test.fixme()` or a `@flaky` tag while they're investigated — don't just silently ignore failures.

### 9.4 Jenkins (good to have, per JD)

Same concepts, different syntax — a `Jenkinsfile` (Groovy-based pipeline-as-code) instead of YAML. If asked in an interview: *"I've worked with GitHub Actions; Jenkins pipelines follow the same core idea — stages for install, build, test, deploy — just declared in a Jenkinsfile instead of a workflow YAML."*

---

## 10. SQL for Data Validation

You likely know MongoDB from MERN — SQL is a different but essential skill for validating relational data behind a compliance product.

### 10.1 Core queries you must know

```sql
-- Basic select
SELECT * FROM cases WHERE status = 'OPEN';

-- Joins (very common — cases + evidence + users)
SELECT c.id, c.title, e.filename, u.username
FROM cases c
JOIN evidence e ON e.case_id = c.id
JOIN users u ON e.uploaded_by = u.id
WHERE c.status = 'SUBMITTED';

-- Aggregates
SELECT status, COUNT(*) as total
FROM cases
GROUP BY status;

-- Filtering with conditions
SELECT * FROM cases
WHERE created_at >= '2026-01-01' AND priority = 'High';

-- Checking for orphaned/inconsistent data (classic data-validation test)
SELECT * FROM evidence
WHERE case_id NOT IN (SELECT id FROM cases);
```

### 10.2 Why an SDET uses SQL

- **Back-end validation**: UI shows "5 open cases" — verify the DB actually has 5 rows with `status='OPEN'`.
- **Test data setup/cleanup**: seed known data before a test run, clean it up after.
- **Debugging**: when a UI test fails, checking the DB directly tells you if it's a UI bug or a data bug.
- **Data integrity checks**: foreign key consistency, no duplicate audit log entries, etc. — especially relevant in a compliance/investigation system.

### 10.3 Practice tip

Set up a free local MySQL/PostgreSQL instance (or use `sqlite3` for zero-setup), create a mock `cases`/`evidence`/`users` schema, and practice joins + aggregates against it. Even 2–3 hours of hands-on practice here will make you comfortable in an interview whiteboard scenario.

---

## 11. Bug Reporting, Triage & Bug Life Cycle

### 11.1 Bug Life Cycle

```
New → Assigned → In Progress → Fixed → Retest → Closed
                                   \
                                    → Reopened (if retest fails)
```

### 11.2 Severity vs Priority (classic interview question — know the difference cold)

- **Severity** = technical impact of the bug (how badly is the system broken?)
- **Priority** = business urgency (how soon must this be fixed?)

Example: A typo in the footer copyright year → **Low severity, Low priority**.
A case's evidence file silently fails to upload with no error shown → **High severity** (data loss risk), and given this is a compliance product, likely **High priority** too.
A crash that only happens on an internal admin tool used once a year → **High severity, Low priority**.

### 11.3 Writing a Good Bug Report

```
Title: Evidence upload silently fails for files >10MB (no error shown to user)

Environment: Staging, Chrome 126, investigator role

Steps to Reproduce:
  1. Log in as investigator
  2. Open Case #1024 (status: Open)
  3. Click "Add Evidence", select a 15MB PDF
  4. Click "Save"

Expected: Either the file uploads successfully, or a clear error message
          explains the size limit.

Actual: The modal closes with no confirmation and no error. The evidence
        list does not update. No entry appears in the audit log either.

Severity: High (silent data loss + missing audit trail — compliance risk)
Priority: High

Attachments: screenshot.png, network-trace.har, console-log.txt
```

Good bug reports are **reproducible, specific, and evidence-backed** — always attach a screenshot, and for E2E automation failures, attach the **Playwright trace** (Section 5.10).

### 11.4 Bug Tracking Tools

Know names even if you haven't used them: Jira, Azure DevOps, Linear, GitHub Issues. The workflow concepts (status, assignee, labels, linked PR) transfer across all of them.

---

## 12. AI-Assisted Testing (Copilot/Claude)

The JD flags this as a "good to have" — here's how to talk about it credibly (don't overclaim).

- **Test scaffolding**: describe a scenario in plain English, have an AI tool draft the first version of a Playwright test — then you review/fix locators and edge cases. AI output is a draft, not ground truth.
- **Generating test data**: asking an AI tool to generate realistic-but-fake sample data (names, case titles, edge-case strings) for negative testing.
- **Explaining unfamiliar code**: pointing an AI assistant at a legacy test file to understand what it does before modifying it.
- **Caution to voice in interview**: AI-generated tests still need human review for correctness, coverage gaps, and whether they actually assert the right thing (an AI can write a test that "passes" without meaningfully verifying behavior).

---

## 13. Portfolio Project Ideas

Since you have MERN experience, build **one polished project** rather than five shallow ones. This becomes your talking point in interviews and your "open-source contribution" equivalent.

### Idea: Automated Test Suite for a Public Demo App

1. Pick a publicly available demo site with realistic CRUD flows — e.g., a demo e-commerce site, or **build your own tiny MERN app** (a mini "case management" app: create/view/update/close a "case" with file upload) — this doubles as a MERN portfolio piece too.
2. Build a Playwright + JavaScript test suite against it:
   - Page Object Model for at least 3 pages (Login, List, Detail)
   - Positive + negative + boundary test cases
   - At least 5 API tests hitting your own backend directly
   - A custom fixture (e.g., authenticated session)
   - Network mocking example (simulate a 500 error)
3. Add a GitHub Actions workflow that runs the suite on every push, uploads the HTML report as an artifact.
4. Write a clean `README.md` explaining: how to run it, folder structure, what's covered, known limitations.
5. Push to a public GitHub repo — this is exactly what "open-source contributions / personal projects" in the JD is asking for.

This single project demonstrates **every required + good-to-have skill** in the JD.

---

## 14. Interview Question Bank

### Conceptual / Testing Fundamentals

1. What's the difference between functional and regression testing?
2. Explain severity vs priority with an example.
3. What is the testing pyramid, and why shouldn't everything be an E2E test?
4. How do you decide what to automate vs. test manually?
5. What causes flaky tests, and how do you fix/prevent them?
6. Walk me through the bug life cycle.
7. What's the difference between smoke and sanity testing?
8. How would you test a login form? (Expect you to cover positive, negative, boundary, security angles — e.g., SQL-injection-style input, very long strings, locked-account behavior.)

### Playwright / Automation Specific

9. Why does Playwright auto-wait, and why is that better than manual sleeps?
10. What's a Page Object Model, and why use one?
11. How would you test a file upload feature?
12. How do you debug a failing test in CI when you can't see the browser?
13. How would you handle a test that depends on data created by a previous test? (Answer: don't — tests should be independent; set up your own data via API in each test/fixture.)
14. How do you test something behind authentication without logging in via UI every single test? (Answer: reuse auth state — `storageState` in Playwright, or fixtures.)
15. How would you mock a slow/erroring API to test the UI's loading/error states?

### API Testing

16. What's the difference between PUT and PATCH?
17. How do you test that an API properly rejects unauthorized requests?
18. What would you check beyond the status code in an API test?
19. How would you test pagination on a `GET /cases?page=2` endpoint?

### Practical / Scenario (compliance-product flavored)

20. This is a compliance/investigation product — what extra testing considerations come to mind? (Good answer: audit trail integrity, role-based access control across investigator/admin/viewer, data retention/deletion rules, no data leakage between cases/tenants, immutability of submitted evidence.)
21. A developer says "this bug is just a UI glitch, low priority" but it hides a data-integrity issue underneath — how do you push back? (Show communication skill + technical judgment, not just "I'd insist.")
22. How would you structure a test suite for a feature that's still actively changing day to day?

### Coding-Round Style (role-specific fundamentals, not DSA)

23. Write a function to validate an email format (regex or manual parsing).
24. Given an array of case objects, write a function to group them by status.
25. Debug this snippet: a Playwright test that clicks a button before the page has finished loading — what's wrong, and fix it.
26. Write a JSDoc comment (or plain object shape) documenting an API response representing a paginated list of cases.

---

## 15. 30-60-90 Day Study Plan

### Days 1–30: Foundations
- Finish Sections 2–4 of this guide (testing fundamentals + TS refresher).
- Install Playwright, run the sample test, break it on purpose (change a locator) to see failure output.
- Write 10 small Playwright tests against any public demo site (positive + negative + boundary cases).
- Learn `codegen` and Trace Viewer hands-on.

### Days 31–60: Framework & API
- Refactor your 10 tests into a proper Page Object Model.
- Add API tests using `request` fixture (Section 7).
- Set up a free MySQL/Postgres instance, practice 15–20 SQL queries (joins, aggregates, filters).
- Push everything to GitHub with a clean README, add the GitHub Actions workflow.

### Days 61–90: Polish & Interview Prep
- Add custom fixtures, network mocking, and at least one negative/security-flavored test to your project.
- Do 2–3 mock interviews (self-recorded or with a friend) using Section 14's question bank.
- Time yourself writing a Playwright test from scratch in under 20 minutes for a given scenario (simulates assessment pressure).
- Review bug report writing (Section 11) — practice writing 3–5 realistic bug reports.

---

## 16. Quick Reference Cheat Sheet

```bash
# Setup
npm init playwright@latest
npx playwright install

# Run
npx playwright test
npx playwright test --headed
npx playwright test --debug
npx playwright test tests/login.spec.js
npx playwright test --grep "login"

# Reports & Debugging
npx playwright show-report
npx playwright show-trace trace.zip
npx playwright codegen <url>
```

```javascript
// Core imports
const { test, expect } = require('@playwright/test');

// Locators priority order: role > label > text > testid > css/xpath (last resort)
page.getByRole('button', { name: 'Save' });
page.getByLabel('Email');
page.getByText('Welcome');
page.getByTestId('case-id-1024');

// Waiting — prefer these over sleep()
await page.waitForSelector('.loaded');
await page.waitForResponse(url);
await page.waitForLoadState('networkidle');

// API testing
const res = await request.get('/api/cases/1024');
expect(res.status()).toBe(200);
```

| Concept | One-line definition |
|---|---|
| Regression testing | Confirming old features still work after a change |
| Smoke testing | Fast shallow "is the build alive" check |
| Flaky test | Passes/fails inconsistently with no code change |
| POM | Design pattern isolating locators/actions per page into reusable classes |
| Idempotent | Calling it multiple times has the same effect as calling once |
| CI | Automatically build+test on every push/PR |
| Severity | Technical impact of a bug |
| Priority | Business urgency of fixing a bug |

---

*Good luck. Given your MERN + C++ OOP background, your programming fundamentals are already solid — the gap you're closing here is testing methodology and the Playwright-specific API, both of which are very learnable in 60–90 days of consistent hands-on practice.*
