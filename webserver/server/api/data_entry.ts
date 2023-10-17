import { Prisma, PrismaClient } from "@prisma/client";

export default defineEventHandler(async (event) => {
  const prisma = new PrismaClient();
  let postBody = await readBody(event);
  let sensor_entry: Prisma.sensor_dataCreateInput
  sensor_entry = postBody;
  const sensor_data = await prisma.sensor_data.create({data: sensor_entry})
});
