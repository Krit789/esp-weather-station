import { Prisma, PrismaClient } from "@prisma/client";

export default defineEventHandler(async (event) => {
  const prisma = new PrismaClient();
  let postBody = await readBody(event);
  let sensor_entry: Prisma.sensor_dataCreateInput
  sensor_entry = postBody;
//   console.log(postBody)
//   postBody = Object.assign({}, postBody, {time : Date.now()})
  const sensor_data = await prisma.sensor_data.create({data: sensor_entry})
//   const sensor_data = await prisma.sensor_data.create({data: {
// 	"temperature": 20.2,
// 	"humidity": 60,
// 	"barometric_pressure": 1100,
// 	"light_intensity": 40
// }})
    console.log(sensor_data)
});
