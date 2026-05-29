--- Creates a table to store private dm status'
CREATE TABLE IF NOT EXISTS private_dms (
    pdm_id INTEGER NOT NULL,
    status INTEGER NOT NULL,
    time TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    UNIQUE(pdm_id)
);