#ifdef TILE_WFC
#include "TileWFCMap2.h"
#include <iostream>
#include <fstream>
#include "base64.h"
#include "StringTrim.h"


TileWFCMap2::TileWFCMap2()
{

}


TileWFCMap2::~TileWFCMap2()
{

}


void TileWFCMap2::setInput(std::string inputFile)
{
  const auto sample_image = load_paletted_image(inputFile.c_str());
  PatternHash foundation = kInvalidHash;
  const auto hashed_patterns = extract_patterns(
    sample_image,
    m_settings.n,
    m_settings.periodic_in,
    m_settings.symmetry,
    nullptr);

	m_model =
  	new OverlappingModel{
  		hashed_patterns,
  		sample_image.palette,
      m_settings.n,
  		m_settings.periodic_out,
  		m_settings.map_width,
  		m_settings.map_height,
  		foundation
  	};

  //
  // Setting up an attempt
  //
  clear();
}


void TileWFCMap2::clear()
{
  m_output = create_output(*m_model);

  m_data.clear();
  m_data.assign(mapwidth * mapheight, -1);

  m_seed = rand();

  //
  // Set the 'm_data' starting areas
  //
  int t, u;
  for (int i = 50 + 4; i < 50 + 23; ++i)
  {
    for (int j = 50 + 11; j < 50 + 21; j++)
    {
      u = 1;
      if (j == 50 + 20 && i == 50 + 12) u = 0;

      t = i + j * mapwidth;
      m_data[t] = u;
    }
  }

  t = (50 + 5) + (50 + 22) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 6) + (50 + 22) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 9) + (50 + 23) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 10) + (50 + 24) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 11) + (50 + 24) * mapwidth; u = 0;
  m_data[t] = u;

  t = (50 + 13) + (50 + 24) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 14) + (50 + 24) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 15) + (50 + 23) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 18) + (50 + 22) * mapwidth; u = 0;
  m_data[t] = u;
  t = (50 + 19) + (50 + 22) * mapwidth; u = 0;
  m_data[t] = u;
}


void TileWFCMap2::stamp(int x, int y, int tile_type)
{
  // Goes into the model
  m_output._changes.set(
    x,
    y,
    true);

  // TODO Loops?
  for (const auto t : irange(m_model->_num_patterns))
  {
    // check pattern... all squares
    //Pattern p = m_model->_patterns[t];
    Pattern p = ((OverlappingModel*)m_model)->_patterns[t];
    for (const auto sub_i : irange(m_settings.n))
    {
      for (const auto sub_j : irange(m_settings.n))
      {
        // if (x - sub_i < 0) continue;
        // if (y - sub_j < 0) continue;

        int sub_t = sub_j * m_settings.n + sub_i;
        if (p[sub_t] == tile_type)
        {
          m_output._wave.set(
            (x + m_model->_width - sub_i) % m_model->_width,
            (y + m_model->_height - sub_j) % m_model->_height,
            t,
            false);
          m_output._changes.set(
            (x + m_model->_width - sub_i) % m_model->_width,
            (y + m_model->_height - sub_j) % m_model->_height,
            true);
        }
      }
    }
  }
}


bool TileWFCMap2::calcPatch(int x, int y)
{
  m_output = create_output(*m_model);

  // Apply stamps from m_data to m_model
  for (int i = 0; i < m_settings.map_width; ++i)
  {
    for (int j = 0; j < m_settings.map_height; j++)
    {
      if (i + x > mapwidth) continue;
      if (j + y > mapheight) continue;

      int t = (i + x) + (j + y) * mapwidth;

      int u = m_data[t];
      if (u != -1)
      {
        stamp(i, j, 1 - u); // ?
      }
    }
  }

  //
  // Run the Model
  //
  const auto result = run(&m_output, *m_model, m_seed, 0);
  m_seed = rand(); // Next seed

  if (result == Result::kSuccess)
  {
    //
    // Save output into Image
    //
    m_image = m_model->image(m_output);

    //
    // Populate data
    //
    for (const auto x1 : irange(m_settings.map_width))
    {
      for (const auto y1 : irange(m_settings.map_height))
      {
        int t = (y + y1) * getMapWidth() + (x + x1);
        m_data[t] = m_image.get(x1, y1).r > 0 ? 1 : 0;
      }
    }
    return true;
  }

  //return calcPatch(x, y); // Try again?

  //
  // result != Result::kSuccess
  //
  for (const auto x1 : irange(m_settings.map_width))
  {
    for (const auto y1 : irange(m_settings.map_height))
    {
      int t = (y + y1) * getMapWidth() + (x + x1);
      m_data[t] = 0;
    }
  }

  return false;
}

#endif
