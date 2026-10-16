# Windows and MySQL acceptance checks

Use test accounts/listings you can identify. Tests that confirm purchases deliberately record orders and reduce stock; do not run them on a real listing you want unchanged. No test data or schema is created automatically by this package.

1. **Designer:** open ProfileSettings.h and PayNow.h in Design view. No database error popup should occur; each fixed control should be selectable. Save a harmless Text change and reopen to check Designer round-trip behavior.
2. **Profile isolation:** log in as account A. Name, email, phone and buyer history must be for A. Close, log in as B and verify B's data. A must not see B's private buyer history.
3. **Name confirmation:** two different names must be rejected. Matching names persist after restart. Email/user ID remain unchanged.
4. **Passwords:** wrong current password, mismatched new passwords and fewer than eight characters must fail. A valid change persists; old login fails and new login succeeds. Do not expose stored password hashes in screenshots.
5. **No seller listings:** Your sells is disabled until the account adds a listing. Create a listing with the existing seller form, reopen settings, and check that Your sells now opens with zero orders/earnings and the listed stock.
6. **Checkout arithmetic:** test listing price Rs. 250.50 and stock 5.000 kg. As another account, buy 1.250 kg. Expected total: Rs. 313.13 (two-decimal rounding away from zero), stock 3.750 kg, one buyer-history order, one seller sale, seller earnings +Rs. 313.13.
7. **Exact remainder:** buy the remaining stock using another checkout. Stock becomes 0.000; no negative stock; card disappears from available market results. Seller listings/history retain the item.
8. **Invalid quantity:** zero, excessive stock and own-item buying cannot complete. Read-only stock, unit price and total cannot be edited.
9. **Competing buyers:** set up a test listing with 1 kg through the seller form. Open it in two app instances logged in as different buyers. Both request 1 kg. Only one order should succeed. Final stock is 0 and exactly one new order exists for that listing.
10. **Price changes:** on a test database only, change a listing's price in Workbench after checkout opens. Confirmation must reject the old quote. Reload must show the new price and recalculated total.
11. **Transaction failure:** on an isolated development copy, cause order INSERT to fail (for example remove INSERT permission for the test connection while retaining update rights). Stock must stay unchanged after rollback. Restore permissions before continuing.
12. **Retry token:** in an isolated integration harness call Checkout twice with the SAME buyer ID, listing ID and valid GUID token. Both calls must return the same order ID, stock must decrease once, and only one order row may exist. Do not reuse that token for another item/buyer. This check needs a small C++/CLI test entry point that calls VegWayStore; it is not run automatically.
13. **Graph:** seller Refresh account should show cumulative order count and rupees across daily points, zero-sale dates included. Values must agree with the read-only aggregate below. Separate app instances update after Refresh/reopen.

Read-only checks in MySQL Workbench:

```sql
SELECT order_id, buyer_userid, seller_userid, vegetable_id,
       quantity_kg, price_per_kg, total_amount, created_at
FROM vegdb.vegway_orders ORDER BY order_id DESC LIMIT 20;

SELECT seller_userid, COUNT(*) AS recorded_orders,
       SUM(quantity_kg) AS sold_kg, SUM(total_amount) AS earnings_rs
FROM vegdb.vegway_orders GROUP BY seller_userid;

SELECT vegetable_id, vegetable_name, quantity_kg
FROM vegdb.vegetables ORDER BY vegetable_id DESC LIMIT 20;

SELECT checkout_token, COUNT(*) AS copies
FROM vegdb.vegway_orders GROUP BY checkout_token HAVING COUNT(*) > 1;
```

The final query should return no rows. The token's UNIQUE key is the database constraint enforcing this.
