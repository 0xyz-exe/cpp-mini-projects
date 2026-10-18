# Expense Tracker

Track income and expenses with category summaries.

## Features
- Record income/expense transactions
- Categories
- Monthly summaries
- Integer cents storage (no float precision issues)
- CSV export
- Persistent storage

## Build & Run
```bash
cmake --build build --target expense_tracker
./build/projects/05-expense-tracker/expense_tracker
```

## Test
```bash
./build/projects/05-expense-tracker/expense_test
```

## Concepts
- Integer arithmetic for currency
- Date handling
- File persistence
- Data aggregation
