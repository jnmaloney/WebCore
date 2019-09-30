#ifdef TILE_WFC
#include "TileWFCMap.h"
#include <iostream>
#include <fstream>
#include "base64.h"
#include "StringTrim.h"


TileWFCMap::TileWFCMap()
{

}


TileWFCMap::~TileWFCMap()
{

}


void TileWFCMap::setInput(std::string inputFile)
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


  const auto hashed_patterns_fast = extract_patterns(
    sample_image,
    m_settings.n - 1,
    m_settings.periodic_in,
    m_settings.symmetry,
    nullptr);

  m_modelFast =
  	new OverlappingModel{
  		hashed_patterns_fast,
  		sample_image.palette,
      m_settings.n - 1,
  		m_settings.periodic_out,
  		m_settings.map_width,
  		m_settings.map_height,
  		foundation
  	};

  //
  // Setting up an attempt
  //
  //m_output = create_output(*m_model);
  clear();
}


void TileWFCMap::clear()
{
  m_outputStamp = create_output(*m_model);
  m_outputNoStamp = create_output(*m_model);
  m_output = &m_outputNoStamp;

  data.clear();
  data.resize(125 * 125);
}


void TileWFCMap::generate()
{
  int seed = rand();

  // int off_x = 50;
  // int off_y = 49;
  int off_x = 10;
  int off_y = 10;
  for (int i = 0; i < 25; ++i)
  {
    for (int j = 1; j < 25; j++)
    {
      int t = 1;
      if (j >= 24 && i == 12) t = 0;
      stamp(off_x + i, off_y + j, t);
    }
  }

  stamp(off_x + 5, off_y + 25, 0);
  stamp(off_x + 6, off_y + 25, 0);

  stamp(off_x + 18, off_y + 25, 0);
  stamp(off_x + 19, off_y + 25, 0);


  const auto result = run(m_output, *m_model, seed, 0);

  if (result == Result::kSuccess)
  {
    m_image = m_model->image(*m_output);
    //g_wm.buildRenderQueues(&image);

    // Populate data
    data.clear();
    //data.resize(m_settings.map_width * m_settings.map_height);
    data.resize(125 * 125);
    for (const auto x : irange(m_settings.map_width))
    {
      for (const auto y : irange(m_settings.map_height))
      {
        //int t = y * m_settings.map_width + x;
        int t = (y + 40) * m_settings.map_width + (x + 40);
        data[t] = m_image.get(x, y).r > 0 ? 1 : 0;
      }
    }
  }
}


void TileWFCMap::stamp(int x, int y, int tile_type)
{
  // m_output._wave.set(
  //   x,
  //   y,
  //   tile_type,
  //   true);
  m_output->_changes.set(
    x,
    y,
    true);

  for (const auto t : irange(m_model->_num_patterns))
  {
    // check pattern... all squares
    //Pattern p = m_model->_patterns[t];
    Pattern p = ((OverlappingModel*)m_model)->_patterns[t];
    for (const auto sub_i : irange(m_settings.n))
    {
      for (const auto sub_j : irange(m_settings.n))
      {
        int sub_t = sub_j * m_settings.n + sub_i;
        if (p[sub_t] == tile_type)
        {
          m_output->_wave.set(
            (x + m_model->_width - sub_i) % m_model->_width,
            (y + m_model->_height - sub_j) % m_model->_height,
            t,
            false);
          m_output->_changes.set(
            (x + m_model->_width - sub_i) % m_model->_width,
            (y + m_model->_height - sub_j) % m_model->_height,
            true);
        }
        // else
        // {
        //   m_output._wave.set(
        //     (x + m_model->_width - sub_i) % m_model->_width,
        //     (y + m_model->_height - sub_j) % m_model->_height,
        //     t,
        //     true);
        //   m_output._changes.set(
        //     (x + m_model->_width - sub_i) % m_model->_width,
        //     (y + m_model->_height - sub_j) % m_model->_height,
        //     true);
        // }
      }
    }
  }
}


bool TileWFCMap::calcPatch(int x, int y, bool do_stamp, bool useFast)
{
  int seed = rand();
  //m_output = create_output(*m_model);

  //
  // Stamping
  //
  if (do_stamp)
  {
    m_output = &m_outputStamp;
    for (int i = 4; i < 23; ++i)
    {
      for (int j = 11; j < 21; j++)
      {
        int t = 1;
        if (j == 20 && i == 12) t = 0;
        //if (j == 21 && i == 12) t = 0;
        stamp(i, j, t);
      }
    }

    stamp(5, 22, 0);
    stamp(6, 22, 0);
    stamp(9, 23, 0);
    stamp(10, 24, 0);
    stamp(11, 24, 0);

    stamp(13, 24, 0);
    stamp(14, 24, 0);
    stamp(15, 23, 0);
    stamp(18, 22, 0);
    stamp(19, 22, 0);
  }
  else
  {
    //m_output = &m_outputNoStamp;
    m_outputNoStamp = create_output(*m_model);
    m_output = &m_outputNoStamp;
  }

  //
  // Border hack
  //
  // if (x > 0)
  // {
  //   for (int j = 0 - m_settings.n; j < m_settings.map_height; ++j)
  //   {
  //     int t = (y + j) * getMapWidth() + (x - 1);
  //     int tile_type = data[t];
  //
  //     for (const auto ip : irange(m_model->_num_patterns))
  //     {
  //       // check pattern... all squares
  //       //Pattern p = m_model->_patterns[t];
  //       Pattern p = ((OverlappingModel*)m_model)->_patterns[ip];
  //
  //       for (int sub_i : irange(m_settings.n))
  //       {
  //         for (int sub_j : irange(m_settings.n))
  //         {
  //           int sub_t = sub_j * m_settings.n + sub_i;
  //           if (p[sub_t] == tile_type)
  //           {
  //             m_output->_wave.set(
  //               (0 + m_model->_width + sub_i) % m_model->_width,
  //               (j + m_model->_height + sub_j) % m_model->_height,
  //               ip,
  //               false);
  //             m_output->_changes.set(
  //               (0 + m_model->_width + sub_i) % m_model->_width,
  //               (j + m_model->_height + sub_j) % m_model->_height,
  //               true);
  //           }
  //
  //         }
  //       }
  //     }
  //   }
  // }
  if (x > 0 && !useFast)
  {
    for (int j = 0; j < m_settings.map_height - 1; ++j)
    {
      int t0 = (y + j) * getMapWidth() + (x - 1);
      int t1 = (y + j + 1) * getMapWidth() + (x - 1);
      int u0 = data[t0];
      int u1 = data[t1];

      if (u0 == 0 && u1 == 1)
      {
        stamp(0, j, 1);
        stamp(0, j+1, 0);
      }

      if (u0 == 1 && u1 == 0)
      {
        stamp(0, j, 0);
        stamp(0, j+1, 1);
      }
    }
  }

  //
  // Run the Model
  //
  const auto result = useFast ?
    run(m_output, *m_modelFast, seed, 0) :
    run(m_output, *m_model, seed, 0);

  if (result == Result::kSuccess)
  {
    //
    // Save output into Image
    //
    m_image = useFast ?
      m_modelFast->image(*m_output) :
      m_model->image(*m_output);
    //g_wm.buildRenderQueues(&image);

    //
    // Populate data
    //
    for (const auto x1 : irange(m_settings.map_width))
    {
      for (const auto y1 : irange(m_settings.map_height))
      {
        int t = (y + y1) * getMapWidth() + (x + x1);
        data[t] = m_image.get(x1, y1).r > 0 ? 1 : 0;
      }
    }
    return true;
  }

  for (const auto x1 : irange(m_settings.map_width))
  {
    for (const auto y1 : irange(m_settings.map_height))
    {
      int t = (y + y1) * getMapWidth() + (x + x1);
      data[t] = 0;
    }
  }

  return false;
}

#endif
