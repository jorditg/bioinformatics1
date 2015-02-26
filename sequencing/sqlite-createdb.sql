SQLite3

CREATE TABLE peptide (
  peptide       VARCHAR(50) PRIMARY KEY, 
  weight        REAL NOT NULL
);

.separator ' ' 
.import peptides.txt peptide

CREATE INDEX idx_weight ON peptide(weight ASC);


SELECT peptide, weight from peptide WHERE weight > 520.2 AND weight < 520.8;
