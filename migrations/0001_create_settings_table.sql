--- Creates a table to store user settings
CREATE TABLE IF NOT EXISTS settings (
    user_id INTEGER,
    typing_notification BOOLEAN,
    allow_private_dms BOOLEAN,
    UNIQUE(user_id)
);