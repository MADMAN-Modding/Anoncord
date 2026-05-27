--- Creates a table to store user settings
CREATE TABLE IF NOT EXISTS settings (
    user_id INTEGER,
    typing_notification BOOLEAN DEFAULT TRUE,
    allow_private_dms BOOLEAN DEFAULT TRUE,
    UNIQUE(user_id)
);