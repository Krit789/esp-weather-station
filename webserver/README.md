# The Forecaster Dashboard with Nuxt 3 Minimal Starter

Look at the [Nuxt 3 documentation](https://nuxt.com/docs/getting-started/introduction) to learn more.

## Setup

Make sure to install the dependencies:

```bash
# npm
npm install

# pnpm
pnpm install

# yarn
yarn install

# bun
bun install
```

## Prisma ORM Setup

Make sure to hook up Prisma to your MySQL-Compatible database by setting up the environment variables in `.env` file

More Info in [Prisma Database connectors - MySQL](https://www.prisma.io/docs/concepts/database-connectors/mysql)
```text

DATABASE_URL=mysql://USER:PASSWORD@HOST:PORT/DATABASE # Replace with your connection string here

```


Then push the database schema to your database

```bash

# npx
npx prisma db push

# pnpx
pnpx prisma db push

```

And finally generate prisma client

```bash

# npx
npx prisma generate

# pnpx
pnpx prisma generate

```


## Development Server

Start the development server on `http://localhost:3000`:

```bash
# npm
npm run dev

# pnpm
pnpm run dev

# yarn
yarn dev

# bun
bun run dev
```

## Production

Build the application for production:

```bash
# npm
npm run build

# pnpm
pnpm run build

# yarn
yarn build

# bun
bun run build
```

Locally preview production build:

```bash
# npm
npm run preview

# pnpm
pnpm run preview

# yarn
yarn preview

# bun
bun run preview
```

Check out the [deployment documentation](https://nuxt.com/docs/getting-started/deployment) for more information.
