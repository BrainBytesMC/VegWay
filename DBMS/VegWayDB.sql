CREATE DATABASE IF NOT EXISTS vegdb
    DEFAULT CHARACTER SET utf8mb4;

USE vegdb;

-- 1. Registered users
CREATE TABLE IF NOT EXISTS users (
    userid INT UNSIGNED NOT NULL AUTO_INCREMENT,
    CustomerName VARCHAR(100) NOT NULL,
    Email VARCHAR(254) NOT NULL,
    Phonenumber VARCHAR(20) NOT NULL,
    Password VARCHAR(255) NOT NULL,

    PRIMARY KEY (userid),
    UNIQUE KEY uq_users_email (Email)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


-- 2. Vegetable listings
CREATE TABLE IF NOT EXISTS vegetables (
    vegetable_id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
    seller_userid INT UNSIGNED NOT NULL,
    vegetable_name VARCHAR(100) NOT NULL,

    category ENUM(
        'Leafy vegetables',
        'Root vegetables',
        'Fruit vegetables',
        'Beans & peas',
        'Other'
    ) NOT NULL DEFAULT 'Other',

    image_data MEDIUMBLOB NULL,
    price_per_kg DECIMAL(10,2) NOT NULL,
    quantity_kg DECIMAL(10,3) NOT NULL,
    location VARCHAR(150) NOT NULL,
    contact_phone VARCHAR(20) NOT NULL,
    is_active TINYINT(1) NOT NULL DEFAULT 1,
    created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (vegetable_id),
    KEY idx_market (is_active, category, created_at),
    KEY idx_seller (seller_userid),

    CONSTRAINT fk_vegetables_seller
        FOREIGN KEY (seller_userid)
        REFERENCES users(userid)
        ON DELETE RESTRICT,

    CONSTRAINT ck_price
        CHECK (price_per_kg > 0),

    CONSTRAINT ck_quantity
        CHECK (quantity_kg >= 0)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


-- 3. Purchases, buyer history and seller earnings
CREATE TABLE IF NOT EXISTS vegway_orders (
    order_id BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,

    checkout_token CHAR(36)
        CHARACTER SET ascii
        COLLATE ascii_bin
        NOT NULL,

    buyer_userid INT UNSIGNED NOT NULL,
    seller_userid INT UNSIGNED NOT NULL,
    vegetable_id BIGINT UNSIGNED NOT NULL,

    item_name VARCHAR(100) NOT NULL,
    quantity_kg DECIMAL(10,3) NOT NULL,
    price_per_kg DECIMAL(10,2) NOT NULL,
    total_amount DECIMAL(18,2) NOT NULL,
    created_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (order_id),
    UNIQUE KEY uq_checkout (checkout_token),
    KEY idx_buyer (buyer_userid, created_at),
    KEY idx_seller (seller_userid, created_at),
    KEY idx_order_item (vegetable_id),

    CONSTRAINT fk_order_buyer
        FOREIGN KEY (buyer_userid)
        REFERENCES users(userid)
        ON DELETE RESTRICT,

    CONSTRAINT fk_order_seller
        FOREIGN KEY (seller_userid)
        REFERENCES users(userid)
        ON DELETE RESTRICT,

    CONSTRAINT fk_order_item
        FOREIGN KEY (vegetable_id)
        REFERENCES vegetables(vegetable_id)
        ON DELETE RESTRICT,

    CONSTRAINT ck_order_quantity
        CHECK (quantity_kg > 0),

    CONSTRAINT ck_order_price
        CHECK (price_per_kg > 0),

    CONSTRAINT ck_order_total
        CHECK (total_amount >= 0)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


-- Confirm the tables exist
SHOW TABLES;