use sqlx::sqlite::{SqliteConnectOptions, SqlitePoolOptions};

#[tokio::main]
async fn main() {
    let database = SqlitePoolOptions::new()
        .connect_with(
            SqliteConnectOptions::new()
                .filename("../settings.sqlite")
                .create_if_missing(true),
        );

    sqlx::migrate!("../migrations")
        .run(&database.await
        .expect("Couldn't connect to database"))
        .await
        .expect("Migration failed");
}