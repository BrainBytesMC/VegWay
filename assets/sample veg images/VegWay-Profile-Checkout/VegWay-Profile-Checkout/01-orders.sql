-- Additive migration for your EXISTING vegdb; no user/listing changes.
-- Requires the users and vegetables definitions previously supplied.
USE vegdb;
CREATE TABLE IF NOT EXISTS vegway_orders (
  order_id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
  checkout_token CHAR(36) CHARACTER SET ascii COLLATE ascii_bin NOT NULL,
  buyer_userid INT UNSIGNED NOT NULL,
  seller_userid INT UNSIGNED NOT NULL,
  vegetable_id BIGINT UNSIGNED NOT NULL,
  item_name VARCHAR(100) NOT NULL,
  quantity_kg DECIMAL(10,3) NOT NULL,
  price_per_kg DECIMAL(10,2) NOT NULL,
  total_amount DECIMAL(18,2) NOT NULL,
  created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(order_id), UNIQUE KEY uq_checkout(checkout_token),
  KEY idx_buyer(buyer_userid,created_at), KEY idx_seller(seller_userid,created_at),
  KEY idx_order_item(vegetable_id),
  CONSTRAINT fk_order_buyer FOREIGN KEY(buyer_userid) REFERENCES users(userid) ON DELETE RESTRICT,
  CONSTRAINT fk_order_seller FOREIGN KEY(seller_userid) REFERENCES users(userid) ON DELETE RESTRICT,
  CONSTRAINT fk_order_item FOREIGN KEY(vegetable_id) REFERENCES vegetables(vegetable_id) ON DELETE RESTRICT,
  CONSTRAINT ck_order_quantity CHECK(quantity_kg>0),
  CONSTRAINT ck_order_price CHECK(price_per_kg>0),
  CONSTRAINT ck_order_total CHECK(total_amount>=0)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
-- These are locally recorded orders, not proof of external payment.
